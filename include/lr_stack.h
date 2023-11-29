/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 00:32:25 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 05:47:44 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lrstack.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The LR stack definition.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

#ifndef LR_STACK_H
# define LR_STACK_H

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

# include <stddef.h>

# include "token.h"
# include "lr_type.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definition.                                                  * //
// *                                                                        * //
// ************************************************************************** //

typedef enum e_lr_stack_item_type {
	ITEM_TOKEN,
	ITEM_DERIVED,
	ITEM_AXIOM,
	ITEM__COUNT,
}	t_lr_stack_item_type;

typedef struct s_lr_stack_derived {
	t_lr_prod_id	prod_id;
	void			*data;
}	t_lr_stack_derived;

typedef union u_lr_stack_item_data {
	t_token				token;
	t_lr_stack_derived	derived;
}	t_lr_stack_item_data;

typedef struct s_lr_stack_item {
	t_lr_stack_item_type	type;
	t_lr_stack_item_data	data;
	t_lr_state_id			state_id;
}	t_lr_stack_item;

typedef struct s_lr_stack {
	t_lr_stack_item	*data;
	size_t			alloced;
	size_t			used;
}	t_lr_stack;

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes.                                                   * //
// *                                                                        * //
// ************************************************************************** //

int				lr_stack_init(
					t_lr_stack *stack
					);

void			lr_stack_destroy(
					t_lr_stack *stack,
					void (*free_derived)(void*)
					);

size_t			lr_stack_used(
					const t_lr_stack *stack
					);

int				lr_stack_push(
					t_lr_stack *stack,
					const t_lr_stack_item *item
					);

int				lr_stack_pop(
					t_lr_stack *stack,
					t_lr_stack_item *item
					);

int				lr_stack_popn(
					t_lr_stack *stack,
					size_t count
					);

t_lr_state_id	lr_stack_cur_state(
					t_lr_stack *stack
					);

#endif
