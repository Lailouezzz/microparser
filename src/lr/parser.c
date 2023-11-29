/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 04:45:46 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 06:09:58 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The LR parser implementation.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "lr_parser.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper function prototypes.                                            * //
// *                                                                        * //
// ************************************************************************** //

static int				_lr_parser_exec(
							t_lr_parser_ctx *ctx,
							t_token *tokens,
							size_t *k
							);

static int				_lr_parser_shift(
							t_lr_parser_ctx *ctx,
							t_token token,
							t_lr_state_id state_id
							);

static int				_lr_parser_reduce(
							t_lr_parser_ctx *ctx,
							t_lr_prod_id prod_id
							);

static t_lr_state_id	_lr_parser_get_goto(
							t_lr_parser_ctx *ctx,
							t_lr_state_id state_id,
							t_lr_prod_id prod_id
							);

static t_lr_prod_cb		_lr_parser_get_prod_cb(
							t_lr_parser_ctx *ctx,
							t_lr_prod_id prod_id
							);

static t_lr_action		_lr_parser_get_action(
							t_lr_parser_ctx *ctx,
							t_token	token
							);

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

int	lr_parser_init(
		t_lr_parser_ctx *ctx
		)
{
	t_lr_stack_item	axiom;

	if (lr_stack_init(&ctx->stack))
		return (1);
	axiom = (t_lr_stack_item){ITEM_AXIOM, {}, 0};
	if (lr_stack_push(&ctx->stack, &axiom))
	{
		lr_stack_destroy(&ctx->stack, NULL);
		return (1);
	}
	return (0);
}

int	lr_parser_exec(
		t_lr_parser_ctx *ctx,
		t_token *tokens,
		size_t nb,
		void **derived
		)
{
	size_t	k;
	int		r;

	k = 0;
	while (k < nb)
	{
		r = _lr_parser_exec(ctx, tokens, &k);
		if (r == 2)
			break ;
		if (r == 1)
			return (1);
	}
	++k;
	if (k != nb || lr_stack_used(&ctx->stack) != 1
		|| ctx->stack.data[0].type != ITEM_DERIVED)
	{
		lr_stack_destroy(&ctx->stack, ctx->free_derived);
		return (1);
	}
	*derived = ctx->stack.data[0].data.derived.data;
	return (0);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

static int	_lr_parser_exec(
				t_lr_parser_ctx *ctx,
				t_token *tokens,
				size_t *k
				)
{
	const t_lr_action	action = _lr_parser_get_action(ctx, tokens[*k]);

	if (action.type == ACTION_ACCEPT)
		return (2);
	else if (action.type == ACTION_SHIFT)
		_lr_parser_shift(ctx, tokens[(*k)++], action.data.shift_id);
	else if (action.type == ACTION_REDUCE)
		_lr_parser_reduce(ctx, action.data.reduce_id);
	else
	{
		lr_stack_destroy(&ctx->stack, ctx->free_derived);
		return (1);
	}
	return (0);
}

static int	_lr_parser_shift(
				t_lr_parser_ctx *ctx,
				t_token token,
				t_lr_state_id state_id
				)
{
	t_lr_stack_item	item;

	item.type = ITEM_TOKEN;
	item.data.token = token;
	item.state_id = state_id;
	return (lr_stack_push(&ctx->stack, &item));
}

static int	_lr_parser_reduce(
				t_lr_parser_ctx *ctx,
				t_lr_prod_id prod_id
				)
{
	const t_lr_prod_cb	prod_cb = _lr_parser_get_prod_cb(ctx, prod_id);
	void				*data;
	t_lr_stack_item		item;

	data = NULL;
	if (prod_cb.cb != NULL)
		data = prod_cb.cb(ctx->stack.data - prod_cb.size);
	if (lr_stack_popn(&ctx->stack, prod_cb.size))
	{
		ctx->free_derived(data);
		return (1);
	}
	item = (t_lr_stack_item){
		.type = ITEM_DERIVED,
		.data.derived = {
		.data = data,
		.prod_id = prod_id,
	},
		_lr_parser_get_goto(ctx, lr_stack_cur_state(&ctx->stack), prod_id),
	};
	return (lr_stack_push(&ctx->stack, &item));
}

static t_lr_state_id	_lr_parser_get_goto(
							t_lr_parser_ctx *ctx,
							t_lr_state_id state_id,
							t_lr_prod_id prod_id
							)
{
	return (ctx->goto_table[ctx->prod_count * state_id + prod_id]);
}

static t_lr_prod_cb	_lr_parser_get_prod_cb(
						t_lr_parser_ctx *ctx,
						t_lr_prod_id prod_id
						)
{
	return (ctx->prod_cb[prod_id]);
}

static t_lr_action	_lr_parser_get_action(
						t_lr_parser_ctx *ctx,
						t_token	token
						)
{
	const t_lr_state_id	cur_state = lr_stack_cur_state(&ctx->stack);

	return (ctx->action_table[ctx->token_count * cur_state + token.type]);
}
