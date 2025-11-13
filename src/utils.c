/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:31:37 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 14:08:29 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The helpers implementation.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "lr_utils.h"

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Reallocate a memory block.
 *
 * Allocates a new block of the requested size, copies the old data into it,
 * and frees the old block. If allocation fails, the old block is still freed.
 *
 * @param p Pointer to the old memory block.
 * @param oldsize Size of the old block in bytes.
 * @param newsize Size of the new block in bytes.
 * @return Pointer to the new block, or NULL on allocation failure.
 */
void	*ft_realloc(
			void *p,
			size_t oldsize,
			size_t newsize
			)
{
	char	*newp;

	newp = malloc(newsize);
	if (newp == NULL)
	{
		free(p);
		return (NULL);
	}
	ft_memcpy(newp, p, oldsize);
	free(p);
	return (newp);
}

/**
 * @brief Copy memory area.
 *
 * Copies n bytes from src to dst. The copy is performed backwards
 * to handle potential overlaps safely.
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
			)
{
	char	*pdst;
	char	*psrc;

	if (n == 0)
		return (dst);
	pdst = (char *)dst;
	psrc = (char *)src;
	while (n-- != 0)
	{
		pdst[n] = psrc[n];
	}
	return (dst);
}

/**
 * @brief Calculate the length of a string.
 *
 * Counts the number of characters in the string until the null terminator.
 *
 * @param str Pointer to null-terminated string.
 * @return Length of the string (excluding null terminator).
 */
int	ft_strlen(
		const char *str
		)
{
	int	k;

	k = 0;
	while (str[k] != '\0')
		++k;
	return (k);
}

/**
 * @brief Duplicate a string.
 *
 * Allocates memory for a new string and copies the content of the
 * original string into it, including the null terminator.
 *
 * @param str Pointer to null-terminated string to duplicate.
 * @return Pointer to the newly allocated duplicate string, or NULL on failure.
 */
char	*ft_strdup(
			const char *str
			)
{
	char	*s;

	s = malloc(ft_strlen(str) + 1);
	if (s == NULL)
		return (NULL);
	return (ft_memcpy(s, str, ft_strlen(str) + 1));
}
