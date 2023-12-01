/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:33:50 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/01 21:30:12 by ale-boud         ###   ########.fr       */
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

# include "lr_token.h"
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
	void	*(*cb)(t_lr_stack_item *item, void *usrptr);
	size_t	size;
	void	(*free_cb)(void *to_free, void *usrptr);
}	t_lr_prod_cb;

typedef struct s_lr_parser_ctx {
	t_lr_prod_cb		*prod_cb;
	t_lr_token_free_cb	*token_free_cbs;
	t_lr_action			*action_table;
	t_lr_state_id		*goto_table;
	size_t				state_count;
	size_t				token_count;
	size_t				prod_count;
	t_lr_stack			stack;
	void				*usrptr;
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
 * @param usrptr The user pointer passed to all callbacks.
 * @return int 0 if success. non null value if error.
 */
int		lr_parser_init(
			t_lr_parser_ctx *ctx,
			void *usrptr
			);

# define MP_ERROR 1
# define MP_ACCEPT 2
# define MP_OK 0

int		lr_parser_exec(
			t_lr_parser_ctx *ctx,
			const t_lr_token *token,
			void **derived
			);

void	lr_parser_destroy(
			t_lr_parser_ctx *ctx
			);

#endif
