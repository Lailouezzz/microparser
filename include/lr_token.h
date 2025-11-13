/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:36:04 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:40:23 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lr_token.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Definition of tokens.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

#ifndef LR_TOKEN_H
# define LR_TOKEN_H

// ************************************************************************** //
// *                                                                        * //
// * Structure definitions.                                                 * //
// *                                                                        * //
// ************************************************************************** //

# ifdef MP_TOKEN_TYPE

/**
 * @brief Token data type.
 *
 * This type is defined by the user through the MP_TOKEN_TYPE macro.
 * It represents the payload data associated with each token.
 */
typedef MP_TOKEN_TYPE	t_lr_token_type;

# else

#  error MP_TOKEN_TYPE must be defined !

# endif

/**
 * @brief Token identifier type.
 *
 * Each token in the grammar is identified by a unique integer value.
 * This identifier is used to index into the action table during parsing.
 */
typedef int				t_lr_token_id;

/**
 * @brief Callback function type for freeing token data.
 *
 * This callback is invoked when a token needs to be destroyed.
 * It is responsible for freeing any resources associated with the token data.
 *
 * @param data Pointer to the token data to be freed.
 */
typedef void			(*t_lr_token_free_cb)(t_lr_token_type *data);

/**
 * @brief Token structure.
 *
 * Represents a token in the LR parser, consisting of an identifier
 * and associated data payload.
 */
typedef struct s_lr_token
{
	t_lr_token_id	id;		/**< Token identifier. */
	t_lr_token_type	data;	/**< Token data payload. */
}	t_lr_token;

#endif
