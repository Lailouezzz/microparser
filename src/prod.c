/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 02:53:20 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 08:49:34 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The prod implementation.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "ast.h"
#include "prod.h"

#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * The production callbacks.                                              * //
// *                                                                        * //
// ************************************************************************** //

const t_lr_prod_cb	g_prod_cbs[PROD__COUNT] = {
[PROD_COMMAND__1] = {_prod_command__1_cb, 1, _prod_command__1_free_cb},
[PROD_COMMAND__2] = {_prod_command__2_cb, 2, _prod_command__2_free_cb},
[PROD_COMMAND_SIMPLE__1] = {_prod_command_simple__1_cb, 1,
	_prod_command_simple__1_free_cb},
[PROD_COMMAND_SIMPLE__2] = {_prod_command_simple__2_cb, 2,
	_prod_command_simple__2_free_cb},
[PROD_ARGS__1] = {_prod_args__1_cb, 1, _prod_args__1_free_cb},
[PROD_ARGS__2] = {_prod_args__2_cb, 2, _prod_args__2_free_cb},
[PROD_PROGNAME] = {_prod_progname_cb, 1, _prod_progname_free_cb},
[PROD_COMMAND_IO__1] = {_prod_command_io__1_cb, 1, _prod_command_io__1_free_cb},
[PROD_COMMAND_IO__2] = {_prod_command_io__2_cb, 2, _prod_command_io__2_free_cb},
[PROD_IO_INFO] = {_prod_io_info_cb, 2, _prod_io_info_free_cb},
};

// ************************************************************************** //
// *                                                                        * //
// * Callback functions.                                                    * //
// *                                                                        * //
// ************************************************************************** //

void	*_prod_command__1_cb(
			t_lr_stack_item *item
			)
{
	(void)(item);
	return (NULL);
}

void	_prod_command__1_free_cb(
			void *to_free
			)
{
	(void)(to_free);
}

void	*_prod_command__2_cb(
			t_lr_stack_item *item
			)
{
	(void)(item);
	return (NULL);
}

void	_prod_command__2_free_cb(
			void *to_free
			)
{
	(void)(to_free);
}

void	*_prod_command_simple__1_cb(
			t_lr_stack_item *item
			)
{
	(void)(item);
	return (NULL);
}

void	_prod_command_simple__1_free_cb(
			void *to_free
			)
{
	(void)(to_free);
}

void	*_prod_command_simple__2_cb(
			t_lr_stack_item *item
			)
{
	(void)(item);
	return (NULL);
}

void	_prod_command_simple__2_free_cb(
			void *to_free
			)
{
	(void)(to_free);
}

void	*_prod_args__1_cb(
			t_lr_stack_item *item
			)
{
	(void)(item);
	return (NULL);
}

void	_prod_args__1_free_cb(
			void *to_free
			)
{
	(void)(to_free);
}

void	*_prod_args__2_cb(
			t_lr_stack_item *item
			)
{
	(void)(item);
	return (NULL);
}

void	_prod_args__2_free_cb(
			void *to_free
			)
{
	(void)(to_free);
}

void	*_prod_progname_cb(
			t_lr_stack_item *item
			)
{
	return (ft_strdup(item->data.token.data.word));
}

void	_prod_progname_free_cb(
			void *to_free
			)
{
	(void)(to_free);
}

void	*_prod_command_io__1_cb(
			t_lr_stack_item *item
			)
{
	(void)(item);
	return (NULL);
}

void	_prod_command_io__1_free_cb(
			void *to_free
			)
{
	(void)(to_free);
}

void	*_prod_command_io__2_cb(
			t_lr_stack_item *item
			)
{
	(void)(item);
	return (NULL);
}

void	_prod_command_io__2_free_cb(
			void *to_free
			)
{
	(void)(to_free);
}

void	*_prod_io_info_cb(
			t_lr_stack_item *item
			)
{
	(void)(item);
	return (NULL);
}

void	_prod_io_info_free_cb(
			void *to_free
			)
{
	(void)(to_free);
}
