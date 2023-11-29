/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:33:50 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 13:40:06 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief LR parser definition.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

#ifndef PARSER_H
# define PARSER_H

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

# include <stdlib.h>

# include "lr/token.h"
# include "lr/type.h"
# include "lr/stack.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definition.                                                  * //
// *                                                                        * //
// ************************************************************************** //

typedef enum e_lr_action_type {
	ACTION_SHIFT,
	ACTION_REDUCE,
	ACTION_ERROR,
	ACTION_ACCEPT,
	ACTION__COUNT,
}	t_lr_action_type;

typedef union u_lr_action_data {
	t_lr_state_id	shift_id;
	t_lr_prod_id	reduce_id;
}	t_lr_action_data;

typedef struct s_lr_action {
	t_lr_action_type	type;
	t_lr_action_data	data;
}	t_lr_action;

typedef struct s_lr_prod_cb {
	void	*(*cb)(t_lr_stack_item *item);
	size_t	size;
	void	(*free_cb)(void *to_free);
}	t_lr_prod_cb;

typedef struct s_lr_parser_ctx {
	t_lr_prod_cb	*prod_cb;
	t_lr_action		*action_table;
	t_lr_state_id	*goto_table;
	size_t			state_count;
	size_t			token_count;
	size_t			prod_count;
	t_lr_stack		stack;
}	t_lr_parser_ctx;

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes.                                                   * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief 
 * @param ctx The parser context.
 * (prod_cb, action_table, goto_table, state_count, token_count, prod_count)
 *     /!\ MUST BE SET.
 * @return int 0 if success. non null value if error.
 */
int		lr_parser_init(
			t_lr_parser_ctx *ctx
			);

int		lr_parser_exec(
			t_lr_parser_ctx *ctx,
			t_lr_token *tokens,
			size_t nb,
			void **derived
			);

void	lr_parser_destroy(
			t_lr_parser_ctx *ctx
			);

#endif
