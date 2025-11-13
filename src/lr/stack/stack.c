/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 04:26:00 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:36:53 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file stack.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief  The LR stack implementation.
 * @date 2023-11-29
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
 * @brief Get the number of items on the stack.
 *
 * @param stack Pointer to the stack.
 * @return Number of items currently on the stack.
 */
size_t	lr_stack_used(
			const t_lr_stack *stack
			)
{
	return (stack->used);
}

/**
 * @brief Push an item onto the stack.
 *
 * Copies the given item onto the top of the stack. If the stack is full,
 * it is automatically grown by doubling its capacity.
 *
 * @param stack Pointer to the stack.
 * @param item Pointer to the item to push.
 * @return LR_OK on success, LR_BAD_ALLOC on allocation failure.
 */
t_lr_error	lr_stack_push(
				t_lr_stack *stack,
				const t_lr_stack_item *item
				)
{
	t_lr_stack_item	*tmp;

	if (stack->used >= stack->alloced)
	{
		tmp = stack->data;
		stack->data
			= ft_realloc(stack->data, stack->alloced * sizeof(*stack->data),
				stack->alloced * 2 * sizeof(*stack->data));
		stack->alloced *= 2;
		if (stack->data == NULL)
		{
			stack->data = tmp;
			return (LR_BAD_ALLOC);
		}
	}
	ft_memcpy(stack->data + stack->used, item, sizeof(*item));
	++stack->used;
	return (LR_OK);
}

/**
 * @brief Pop an item from the stack.
 *
 * Removes the top item from the stack and optionally copies it to
 * the provided buffer. The item is not freed by this function.
 *
 * @param stack Pointer to the stack.
 * @param item Optional pointer to receive the popped item (can be NULL).
 * @return LR_OK on success, LR_INTERNAL_ERROR if stack is empty.
 */
t_lr_error	lr_stack_pop(
				t_lr_stack *stack,
				t_lr_stack_item *item
				)
{
	if (stack->used <= 0)
		return (LR_INTERNAL_ERROR);
	if (item != NULL)
		ft_memcpy(item, stack->data + (stack->used - 1), sizeof(*item));
	--stack->used;
	return (LR_OK);
}

/**
 * @brief Pop multiple items from the stack.
 *
 * Removes count items from the top of the stack without freeing them.
 * This is used during reduce operations.
 *
 * @param stack Pointer to the stack.
 * @param count Number of items to pop.
 * @return LR_OK on success, LR_INTERNAL_ERROR if not enough items on stack.
 */
t_lr_error	lr_stack_popn(
				t_lr_stack *stack,
				size_t count
				)
{
	t_lr_error	err;

	while (count-- != 0)
	{
		err = lr_stack_pop(stack, NULL);
		if (err != LR_OK)
			return (err);
	}
	return (LR_OK);
}

/**
 * @brief Get the current state ID from the top of the stack.
 *
 * Returns the state ID associated with the top item on the stack.
 * This is used to determine the current parser state.
 *
 * @param stack Pointer to the stack.
 * @return The state ID of the top stack item.
 */
t_lr_state_id	lr_stack_cur_state(
					t_lr_stack *stack
					)
{
	return (stack->data[stack->used - 1].state_id);
}
