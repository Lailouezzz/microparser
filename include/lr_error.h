/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:10:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:39:54 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lr_error.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Error definition.
 * @date 2023-12-14
 * @copyright Copyright (c) 2023
 */

#ifndef LR_ERROR_H
# define LR_ERROR_H

// ************************************************************************** //
// *                                                                        * //
// * Error definition.                                                      * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Error codes returned by the LR parser functions.
 *
 * This enumeration defines all possible error codes that can be returned
 * by the LR parser during parsing operations.
 */
typedef enum e_lr_error
{
	/** @brief Success, operation completed without errors. */
	LR_OK,
	/** @brief Input successfully parsed, parsing completed. */
	LR_ACCEPT,
	/** @brief Memory allocation failure. */
	LR_BAD_ALLOC,
	/** @brief Syntax error encountered during parsing. */
	LR_SYNTAX_ERROR,
	/** @brief Production callback returned NULL, indicating an error. */
	LR_PROD_ERROR,
	/** @brief Internal parser error, possibly due to malformed LR tables. */
	LR_INTERNAL_ERROR,
}	t_lr_error;

#endif
