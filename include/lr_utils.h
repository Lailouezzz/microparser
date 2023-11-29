/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 04:16:04 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 14:08:14 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lr_utils.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The helpers definition.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

#ifndef LR_UTILS_H
# define LR_UTILS_H

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

# include <stdlib.h>

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes.                                                   * //
// *                                                                        * //
// ************************************************************************** //

void	*ft_realloc(
			void *p,
			size_t oldsize,
			size_t newsize
			);

void	*ft_memcpy(
			void *dst,
			const void *src,
			size_t n
			);

int		ft_strlen(
			const char *str
			);

char	*ft_strdup(
			const char *str
			);

#endif
