/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 06:12:13 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 07:55:20 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The main testing mouahahahah
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <stdlib.h>

#include "lr_parser.h"
#include "prod.h"
#include "token.h"
#include "table.h"

t_token	g_tokens[] = {
{.type = TOKEN_WORD, .data.word = "cat"},
{.type = TOKEN_WORD, .data.word = "file"},
{.type = TOKEN_WORD, .data.word = "bite"},
{.type = TOKEN_IO, .data.io_type = IO_IN},
{.type = TOKEN_WORD, .data.word = "coiuille"},
{.type = TOKEN_IO, .data.io_type = IO_OUT},
{.type = TOKEN_WORD, .data.word = "zizi"},
{.type = TOKEN_END, {}},
};

int	main(void)
{
	t_lr_parser_ctx	ctx;
	void			*data;

	ctx.action_table = (t_lr_action *)g_lr_table;
	ctx.prod_count = PROD__COUNT;
	ctx.state_count = STATE__COUNT;
	ctx.token_count = TOKEN__COUNT;
	ctx.goto_table = (t_lr_state_id *)g_lr_goto_table;
	ctx.prod_cb = (t_lr_prod_cb *)g_prod_cbs;
	if (lr_parser_init(&ctx))
		return (EXIT_FAILURE);
	if (lr_parser_exec(&ctx, g_tokens, sizeof(g_tokens) / sizeof(*g_tokens),
			&data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
