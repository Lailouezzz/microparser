/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:33:50 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:33:15 by ale-boud         ###   ########.fr       */
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
# include "lr_error.h"
# include "lr_stack.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definition.                                                  * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Type of LR parser action.
 *
 * Defines the possible actions the parser can take when processing a token.
 */
typedef enum e_lr_action_type
{
	ACTION_SHIFT,	/**< Shift action: push token onto stack. */
	ACTION_REDUCE,	/**< Reduce action: apply production rule. */
	ACTION_ERROR,	/**< Error action: syntax error encountered. */
	ACTION_ACCEPT,	/**< Accept action: parsing completed successfully. */
	ACTION__COUNT,	/**< Number of action types. */
}	t_lr_action_type;

/**
 * @brief Union containing data for parser actions.
 *
 * Holds either the target state ID for shift actions or the production ID
 * for reduce actions.
 */
typedef union u_lr_action_data
{
	t_lr_state_id	shift_id;	/**< Target state ID for shift actions. */
	t_lr_prod_id	reduce_id;	/**< Production ID for reduce actions. */
}	t_lr_action_data;

/**
 * @brief Parser action structure.
 *
 * Represents an action to be taken by the parser, including its type
 * and associated data.
 */
typedef struct s_lr_action
{
	t_lr_action_type	type;	/**< Type of action. */
	t_lr_action_data	data;	/**< Data associated with the action. */
}	t_lr_action;

/**
 * @brief Production callback structure.
 *
 * Defines a callback function to be invoked when reducing by a production rule,
 * along with metadata about the production.
 */
typedef struct s_lr_prod_cb
{
	void	*(*cb)(t_lr_stack_item *item, void *usrptr);	/**< Callback to create derived value. */
	size_t	size;											/**< Number of items this production consumes. */
	void	(*free_cb)(void *to_free, void *usrptr);		/**< Callback to free derived value. */
}	t_lr_prod_cb;

/**
 * @brief LR parser context structure.
 *
 * Contains all the state and tables needed to execute the LR parsing algorithm,
 * including action and goto tables, production callbacks, and the parsing stack.
 */
typedef struct s_lr_parser_ctx
{
	t_lr_prod_cb		*prod_cb;			/**< Array of production callbacks. */
	t_lr_token_free_cb	*token_free_cbs;	/**< Array of token free callbacks. */
	t_lr_action			*action_table;		/**< Action table (state × token). */
	t_lr_state_id		*goto_table;		/**< Goto table (state × production). */
	size_t				state_count;		/**< Number of states in the parser. */
	size_t				token_count;		/**< Number of terminal symbols. */
	size_t				prod_count;			/**< Number of production rules. */
	t_lr_stack			stack;				/**< Parsing stack. */
	void				*usrptr;			/**< User pointer passed to callbacks. */
}	t_lr_parser_ctx;

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes.                                                   * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Initialize the LR parser context.
 *
 * Sets up the parser stack and prepares the parser for execution.
 * Before calling this function, the following fields MUST be set:
 * prod_cb, token_free_cbs, action_table, goto_table, state_count,
 * token_count, prod_count.
 *
 * @param ctx Pointer to the parser context to initialize.
 * @param usrptr User pointer passed to all callbacks.
 * @return LR_OK on success, error code otherwise.
 */
int				lr_parser_init(
					t_lr_parser_ctx *ctx,
					void *usrptr
					);

/**
 * @brief Execute one step of LR parsing.
 *
 * Processes a single token and performs the appropriate action (shift, reduce,
 * accept, or error). This function may need to be called multiple times for
 * the same token if reductions occur.
 *
 * @param ctx Pointer to the parser context.
 * @param token Pointer to the token to process.
 * @param derived Output pointer to receive the final derived value on accept.
 * @return LR_ACCEPT on successful parse completion, LR_OK if more tokens needed,
 *         error code on failure.
 */
t_lr_error		lr_parser_exec(
					t_lr_parser_ctx *ctx,
					const t_lr_token *token,
					void **derived
					);

/**
 * @brief Destroy the parser context and free all resources.
 *
 * Frees the parser stack and all associated data.
 *
 * @param ctx Pointer to the parser context to destroy.
 */
void			lr_parser_destroy(
					t_lr_parser_ctx *ctx
					);

// ************************************************************************** //
// *                                                                        * //
// * Private function.                                                      * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Internal parser execution function.
 *
 * Recursively processes a token, performing shifts and reductions as needed.
 *
 * @param ctx Pointer to the parser context.
 * @param tokens Pointer to the current token.
 * @return LR_ACCEPT, LR_OK, or error code.
 */
t_lr_error		_lr_parser_exec(
					t_lr_parser_ctx *ctx,
					const t_lr_token *tokens
					);

/**
 * @brief Perform a shift action.
 *
 * Pushes the given token onto the stack with the specified state ID.
 *
 * @param ctx Pointer to the parser context.
 * @param token Token to shift.
 * @param state_id Target state ID.
 * @return LR_OK on success, error code on failure.
 */
t_lr_error		_lr_parser_shift(
					t_lr_parser_ctx *ctx,
					t_lr_token token,
					t_lr_state_id state_id
					);

/**
 * @brief Perform a reduce action.
 *
 * Pops items from the stack, invokes the production callback to create
 * a derived value, and pushes the result back onto the stack.
 *
 * @param ctx Pointer to the parser context.
 * @param prod_id Production rule ID to reduce by.
 * @return LR_OK on success, error code on failure.
 */
t_lr_error		_lr_parser_reduce(
					t_lr_parser_ctx *ctx,
					t_lr_prod_id prod_id
					);

/**
 * @brief Get the goto state from the goto table.
 *
 * @param ctx Pointer to the parser context.
 * @param state_id Current state ID.
 * @param prod_id Production ID.
 * @return The target state ID from the goto table.
 */
t_lr_state_id	_lr_parser_get_goto(
					t_lr_parser_ctx *ctx,
					t_lr_state_id state_id,
					t_lr_prod_id prod_id
					);

/**
 * @brief Get the parser action for the current state and token.
 *
 * @param ctx Pointer to the parser context.
 * @param token Pointer to the current token.
 * @return The action to perform.
 */
t_lr_action		_lr_parser_get_action(
					t_lr_parser_ctx *ctx,
					const t_lr_token *token
					);

#endif
