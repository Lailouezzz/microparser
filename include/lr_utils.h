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

/**
 * @brief Reallocate memory block.
 *
 * Allocates a new block of memory, copies the old data to it,
 * and frees the old block. If allocation fails, the old block is freed.
 *
 * @param p Pointer to the old memory block.
 * @param oldsize Size of the old memory block in bytes.
 * @param newsize Size of the new memory block in bytes.
 * @return Pointer to the new memory block, or NULL on allocation failure.
 */
void	*ft_realloc(
			void *p,
			size_t oldsize,
			size_t newsize
			);

/**
 * @brief Copy memory area.
 *
 * Copies n bytes from src to dst. The memory areas may overlap.
 * Implementation copies backwards to handle overlaps.
 *
 * @param dst Pointer to destination memory area.
 * @param src Pointer to source memory area.
 * @param n Number of bytes to copy.
 * @return Pointer to dst.
 */
void	*ft_memcpy(
			void *dst,
			const void *src,
			size_t n
			);

/**
 * @brief Calculate the length of a string.
 *
 * @param str Pointer to null-terminated string.
 * @return Length of the string (excluding null terminator).
 */
int		ft_strlen(
			const char *str
			);

/**
 * @brief Duplicate a string.
 *
 * Allocates memory and copies the given string into it.
 *
 * @param str Pointer to null-terminated string to duplicate.
 * @return Pointer to the newly allocated string, or NULL on allocation failure.
 */
char	*ft_strdup(
			const char *str
			);

#endif
