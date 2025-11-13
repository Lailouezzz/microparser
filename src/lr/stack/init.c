/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:36:25 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:40:16 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file init.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Stack init and destroy function.
 * @date 2023-12-14
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "lr_stack.h"

#include "lr_utils.h"

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Initialize a parser stack.
 *
 * Allocates initial memory for the stack and sets up the token free callbacks.
 * The stack starts with an initial capacity of 1 item.
 *
 * @param stack Pointer to the stack to initialize.
 * @param token_free_cbs Array of token free callbacks indexed by token ID.
 * @param usrptr User pointer passed to all callbacks.
 * @return LR_OK on success, LR_BAD_ALLOC on allocation failure.
 */
t_lr_error	lr_stack_init(
				t_lr_stack *stack,
				t_lr_token_free_cb *token_free_cbs,
				void *usrptr
				)
{
	stack->used = 0;
	stack->alloced = 1;
	stack->token_free_cbs = token_free_cbs;
	stack->usrptr = usrptr;
	stack->data = malloc(stack->alloced * sizeof(*stack->data));
	if (stack->data == NULL)
		return (LR_BAD_ALLOC);
	return (LR_OK);
}

/**
 * @brief Destroy a parser stack and free all resources.
 *
 * Iterates through all items on the stack and frees them by calling their
 * appropriate callbacks. Then frees the stack array itself and resets counters.
 *
 * @param stack Pointer to the stack to destroy.
 */
void	lr_stack_destroy(
			t_lr_stack *stack
			)
{
	size_t	k;

	k = 0;
	while (k < stack->used)
	{
		if (stack->data[k].type == ITEM_DERIVED
			&& stack->data[k].data.derived.prod_free_cb != NULL)
			stack->data[k].data.derived.prod_free_cb(
				stack->data[k].data.derived.data, stack->usrptr);
		else if (stack->data[k].type == ITEM_TOKEN
			&& stack->token_free_cbs[stack->data[k].data.token.id] != NULL)
			stack->token_free_cbs[stack->data[k].data.token.id](
				&stack->data[k].data.token.data);
		++k;
	}
	free(stack->data);
	stack->used = 0;
	stack->alloced = 0;
}
