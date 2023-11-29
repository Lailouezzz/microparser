/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 04:26:00 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 11:14:32 by ale-boud         ###   ########.fr       */
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

#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

int	lr_stack_init(
		t_lr_stack *stack
		)
{
	stack->used = 0;
	stack->alloced = 1;
	stack->data = malloc(stack->alloced * sizeof(*stack->data));
	return (stack->data == NULL);
}

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
				stack->data[k].data.derived.data);
		++k;
	}
	free(stack->data);
	stack->used = 0;
	stack->alloced = 0;
}

size_t	lr_stack_used(
			const t_lr_stack *stack
			)
{
	return (stack->used);
}

int	lr_stack_push(
		t_lr_stack *stack,
		const t_lr_stack_item *item
		)
{
	if (stack->used >= stack->alloced)
	{
		stack->data
			= ft_realloc(stack->data, stack->alloced * sizeof(*stack->data),
				stack->alloced * 2 * sizeof(*stack->data));
		stack->alloced *= 2;
		if (stack->data == NULL)
			return (1);
	}
	ft_memcpy(stack->data + stack->used, item, sizeof(*item));
	++stack->used;
	return (0);
}

int	lr_stack_pop(
		t_lr_stack *stack,
		t_lr_stack_item *item
		)
{
	if (stack->used <= 0)
		return (1);
	if (item != NULL)
		ft_memcpy(item, stack->data + (stack->used - 1), sizeof(*item));
	--stack->used;
	return (0);
}

int	lr_stack_popn(
		t_lr_stack *stack,
		size_t count
		)
{
	while (count-- != 0)
		if (lr_stack_pop(stack, NULL))
			return (1);
	return (0);
}

t_lr_state_id	lr_stack_cur_state(
					t_lr_stack *stack
					)
{
	return (stack->data[stack->used - 1].state_id);
}
