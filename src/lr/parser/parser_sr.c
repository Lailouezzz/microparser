/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:24:21 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:40:12 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_sr.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Parser shift reduce implementation
 * @date 2023-12-14
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                           * //
// *                                                                        * //
// ************************************************************************** //

#include "lr_parser.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

t_lr_error	_lr_parser_exec(
						t_lr_parser_ctx *ctx,
						const t_lr_token *token
						)
{
	const t_lr_action	action = _lr_parser_get_action(ctx, token);
	t_lr_error			err;

	if (action.type == ACTION_ACCEPT)
		return (LR_ACCEPT);
	else if (action.type == ACTION_SHIFT)
	{
		err = _lr_parser_shift(ctx, *token, action.data.shift_id);
		if (err != LR_OK)
			return (lr_stack_destroy(&ctx->stack), err);
	}
	else if (action.type == ACTION_REDUCE)
	{
		err = _lr_parser_reduce(ctx, action.data.reduce_id);
		if (err != LR_OK)
			return (lr_stack_destroy(&ctx->stack), err);
	}
	else if (action.type == ACTION_ERROR)
		return (lr_stack_destroy(&ctx->stack), LR_SYNTAX_ERROR);
	if (action.type != ACTION_SHIFT)
		return (_lr_parser_exec(ctx, token));
	return (LR_OK);
}

t_lr_error	_lr_parser_shift(
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

t_lr_error	_lr_parser_reduce(
				t_lr_parser_ctx *ctx,
				t_lr_prod_id prod_id
				)
{
	const t_lr_prod_cb	prod_cb = ctx->prod_cb[prod_id];
	void				*data;
	t_lr_stack_item		item;

	data = prod_cb.cb(ctx->stack.data + ctx->stack.used - prod_cb.size,
			ctx->usrptr);
	if (lr_stack_popn(&ctx->stack, prod_cb.size))
	{
		if (prod_cb.free_cb != NULL)
			prod_cb.free_cb(data, ctx->usrptr);
		return (1);
	}
	if (prod_cb.cb != NULL && data == NULL)
		return (1);
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

t_lr_state_id	_lr_parser_get_goto(
							t_lr_parser_ctx *ctx,
							t_lr_state_id state_id,
							t_lr_prod_id prod_id
							)
{
	return (ctx->goto_table[ctx->prod_count * state_id + prod_id]);
}

t_lr_action	_lr_parser_get_action(
						t_lr_parser_ctx *ctx,
						const t_lr_token *token
						)
{
	const t_lr_state_id	cur_state = lr_stack_cur_state(&ctx->stack);

	return (ctx->action_table[ctx->token_count * cur_state + token->id]);
}
