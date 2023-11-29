/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:36:04 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 13:41:40 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file token.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Definition of tokens.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

#ifndef TOKEN_H
# define TOKEN_H

// ************************************************************************** //
// *                                                                        * //
// * Structure definitions.                                                 * //
// *                                                                        * //
// ************************************************************************** //

typedef int	t_lr_token_id;

typedef struct s_lr_token {
	t_lr_token_id	id;
	void			*data;
}	t_lr_token;

#endif
