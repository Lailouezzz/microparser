/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:36:04 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/01 20:17:29 by ale-boud         ###   ########.fr       */
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

typedef MP_TOKEN_TYPE	t_lr_token_type;

# else

#  error MP_TOKEN_TYPE must be defined !

# endif

typedef int				t_lr_token_id;

typedef void			(*t_lr_token_free_cb)(t_lr_token_type *data);

typedef struct s_lr_token {
	t_lr_token_id	id;
	t_lr_token_type	data;
}	t_lr_token;

#endif
