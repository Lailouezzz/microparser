/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_type.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 02:47:15 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 13:51:08 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lr_type.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The types definition for LR parser.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

#ifndef LR_TYPE_H
# define LR_TYPE_H

// ************************************************************************** //
// *                                                                        * //
// * Typedefs.                                                              * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Identifier for LR parser states.
 *
 * This type represents the state identifier in the LR parsing automaton.
 * Each state in the parsing table is identified by a unique integer value.
 */
typedef int	t_lr_state_id;

/**
 * @brief Identifier for production rules.
 *
 * This type represents a production rule identifier in the grammar.
 * Each production rule used for reductions is identified by a unique integer.
 */
typedef int	t_lr_prod_id;

#endif
