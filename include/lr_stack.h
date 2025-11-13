/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 00:32:25 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:20:20 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lr_stack.h
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

# include "lr_token.h"
# include "lr_error.h"
# include "lr_type.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definition.                                                  * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Type of item stored in the LR stack.
 *
 * Identifies whether a stack item contains a token, a derived value
 * from a production, or the axiom (initial state).
 */
typedef enum e_lr_stack_item_type
{
	ITEM_TOKEN,		/**< Stack item contains a token. */
	ITEM_DERIVED,	/**< Stack item contains a derived value. */
	ITEM_AXIOM,		/**< Stack item contains the axiom (initial state). */
	ITEM__COUNT,	/**< Number of item types. */
}	t_lr_stack_item_type;

/**
 * @brief Derived value structure.
 *
 * Represents a value derived from applying a production rule.
 * Contains the data and its associated free callback.
 */
typedef struct s_lr_stack_derived
{
	void	(*prod_free_cb)(void *to_free, void *usrptr);	/**< Callback to free the derived data. */
	void	*data;											/**< Pointer to the derived data. */
}	t_lr_stack_derived;

/**
 * @brief Union for stack item data.
 *
 * Holds either a token or a derived value, depending on the item type.
 */
typedef union u_lr_stack_item_data
{
	t_lr_token			token;		/**< Token data. */
	t_lr_stack_derived	derived;	/**< Derived data. */
}	t_lr_stack_item_data;

/**
 * @brief Stack item structure.
 *
 * Represents a single item on the LR parser stack, containing the item type,
 * its associated data, and the parser state ID.
 */
typedef struct s_lr_stack_item
{
	t_lr_stack_item_type	type;		/**< Type of the stack item. */
	t_lr_stack_item_data	data;		/**< Data associated with the item. */
	t_lr_state_id			state_id;	/**< Parser state ID at this stack level. */
}	t_lr_stack_item;

/**
 * @brief LR parser stack structure.
 *
 * Dynamic stack implementation for the LR parser. Grows automatically
 * as needed and manages memory for tokens and derived values.
 */
typedef struct s_lr_stack
{
	t_lr_stack_item		*data;				/**< Array of stack items. */
	t_lr_token_free_cb	*token_free_cbs;	/**< Array of token free callbacks. */
	size_t				alloced;			/**< Allocated capacity. */
	size_t				used;				/**< Number of items currently on stack. */
	void				*usrptr;			/**< User pointer passed to callbacks. */
}	t_lr_stack;

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes.                                                   * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Initialize an LR parser stack.
 *
 * Allocates initial memory for the stack and sets up the token free callbacks.
 *
 * @param stack Pointer to the stack structure to initialize.
 * @param token_free_cbs Array of token free callbacks indexed by token ID.
 * @param usrptr User pointer passed to all callbacks.
 * @return LR_OK on success, LR_BAD_ALLOC on allocation failure.
 */
t_lr_error		lr_stack_init(
					t_lr_stack *stack,
					t_lr_token_free_cb *token_free_cbs,
					void *usrptr
					);

/**
 * @brief Destroy an LR parser stack and free all resources.
 *
 * Frees all items on the stack by calling appropriate callbacks,
 * then frees the stack array itself.
 *
 * @param stack Pointer to the stack to destroy.
 */
void			lr_stack_destroy(
					t_lr_stack *stack
					);

/**
 * @brief Get the number of items currently on the stack.
 *
 * @param stack Pointer to the stack.
 * @return Number of items currently on the stack.
 */
size_t			lr_stack_used(
					const t_lr_stack *stack
					);

/**
 * @brief Push an item onto the stack.
 *
 * Grows the stack automatically if needed. Copies the item onto the stack.
 *
 * @param stack Pointer to the stack.
 * @param item Pointer to the item to push.
 * @return LR_OK on success, LR_BAD_ALLOC on allocation failure.
 */
t_lr_error		lr_stack_push(
					t_lr_stack *stack,
					const t_lr_stack_item *item
					);

/**
 * @brief Pop an item from the stack.
 *
 * Removes the top item from the stack and optionally copies it to the
 * provided buffer.
 *
 * @param stack Pointer to the stack.
 * @param item Optional pointer to receive the popped item (can be NULL).
 * @return LR_OK on success, LR_INTERNAL_ERROR if stack is empty.
 */
t_lr_error		lr_stack_pop(
					t_lr_stack *stack,
					t_lr_stack_item *item
					);

/**
 * @brief Pop multiple items from the stack.
 *
 * Removes count items from the top of the stack. Items are not freed,
 * they are simply removed from the stack.
 *
 * @param stack Pointer to the stack.
 * @param count Number of items to pop.
 * @return LR_OK on success, LR_INTERNAL_ERROR if not enough items on stack.
 */
t_lr_error		lr_stack_popn(
					t_lr_stack *stack,
					size_t count
					);

/**
 * @brief Get the current state ID from the top of the stack.
 *
 * @param stack Pointer to the stack.
 * @return The state ID of the top stack item.
 */
t_lr_state_id	lr_stack_cur_state(
					t_lr_stack *stack
					);

#endif
