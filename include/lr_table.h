/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_table.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 02:31:34 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 04:03:30 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lr_table.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The LR tables definition.
 * @see	https://dpt-info-sciences.univ-rouen.fr/~bedonnic/ :3
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

#ifndef LR_TABLE_H
# define LR_TABLE_H

// ************************************************************************** //
// *                                                                        * //
// * Defines.                                                              * //
// *                                                                        * //
// ************************************************************************** //

# define STATE__COUNT 13

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

# include "token.h"
# include "prod.h"
# include "lr_parser.h"

// ************************************************************************** //
// *                                                                        * //
// * LR tables definition.                                                  * //
// *                                                                        * //
// ************************************************************************** //

extern const t_lr_action	g_lr_table[STATE__COUNT][TOKEN__COUNT];
extern const t_lr_state_id	g_lr_goto_table[STATE__COUNT][PROD__COUNT];

#endif
