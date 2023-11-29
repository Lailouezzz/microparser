/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:33:50 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 06:08:02 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lr_parser.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief LR parser definition.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

#ifndef LR_PARSER_H
# define LR_PARSER_H

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

# include <stdlib.h>

# include "lr_type.h"
# include "lr_stack.h"

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
}	t_lr_prod_cb;

typedef struct s_lr_parser_ctx {
	t_lr_prod_cb	*prod_cb;
	t_lr_action		*action_table;
	t_lr_state_id	*goto_table;
	size_t			state_count;
	size_t			token_count;
	size_t			prod_count;
	void			(*free_derived)(void*);
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
			t_token *tokens,
			size_t nb,
			void **derived
			);

#endif