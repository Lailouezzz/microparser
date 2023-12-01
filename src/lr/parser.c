/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 04:45:46 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/01 22:56:26 by ale-boud         ###   ########.fr       */
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
							const t_lr_token *tokens
							);

static int				_lr_parser_shift(
							t_lr_parser_ctx *ctx,
							t_lr_token token,
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
							const t_lr_token *token
							);

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

int	lr_parser_init(
		t_lr_parser_ctx *ctx,
		void *usrptr
		)
{
	t_lr_stack_item	axiom;

	if (lr_stack_init(&ctx->stack, ctx->token_free_cbs, usrptr))
		return (1);
	axiom = (t_lr_stack_item){.type = ITEM_AXIOM, .data = {}, .state_id = 0};
	if (lr_stack_push(&ctx->stack, &axiom))
	{
		lr_stack_destroy(&ctx->stack);
		return (1);
	}
	ctx->usrptr = usrptr;
	return (0);
}

int	lr_parser_exec(
		t_lr_parser_ctx *ctx,
		const t_lr_token *token,
		void **derived
		)
{
	int	r;

	r = _lr_parser_exec(ctx, token);
	if (r != MP_ACCEPT)
		return (r);
	if (lr_stack_used(&ctx->stack) != 2)
	{
		lr_stack_destroy(&ctx->stack);
		return (MP_ERROR);
	}
	*derived = ctx->stack.data[1].data.derived.data;
	ctx->stack.used = 1;
	return (MP_ACCEPT);
}

void	lr_parser_destroy(
			t_lr_parser_ctx *ctx
			)
{
	lr_stack_destroy(&ctx->stack);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

static int	_lr_parser_exec(
				t_lr_parser_ctx *ctx,
				const t_lr_token *token
				)
{
	const t_lr_action	action = _lr_parser_get_action(ctx, token);

	if (action.type == ACTION_ACCEPT)
		return (MP_ACCEPT);
	else if (action.type == ACTION_SHIFT
		&& _lr_parser_shift(ctx, *token, action.data.shift_id))
	{
		lr_stack_destroy(&ctx->stack);
		return (MP_ERROR);
	}
	else if (action.type == ACTION_REDUCE
		&& _lr_parser_reduce(ctx, action.data.reduce_id))
	{
		lr_stack_destroy(&ctx->stack);
		return (MP_ERROR);
	}
	else if (action.type == ACTION_ERROR)
	{
		lr_stack_destroy(&ctx->stack);
		return (MP_ERROR);
	}
	if (action.type != ACTION_SHIFT)
		return (_lr_parser_exec(ctx, token));
	return (MP_OK);
}

static int	_lr_parser_shift(
				t_lr_parser_ctx *ctx,
				t_lr_token token,
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
		data = prod_cb.cb(ctx->stack.data + ctx->stack.used - prod_cb.size,
				ctx->usrptr);
	if (prod_cb.cb != NULL && data == NULL)
		return (1);
	if (lr_stack_popn(&ctx->stack, prod_cb.size))
	{
		if (prod_cb.free_cb != NULL)
			prod_cb.free_cb(data, ctx->usrptr);
		return (1);
	}
	item = (t_lr_stack_item){
		.type = ITEM_DERIVED,
		.data.derived = {
		.data = data,
		.prod_free_cb = prod_cb.free_cb,
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
						const t_lr_token *token
						)
{
	const t_lr_state_id	cur_state = lr_stack_cur_state(&ctx->stack);

	return (ctx->action_table[ctx->token_count * cur_state + token->id]);
}
