/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:28:51 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 21:03:57 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

int	handle_redir_wrapper(t_token *tok, t_gen_list_iter *it, t_command **cmd)
{
	t_token	*file_tok;

	file_tok = gen_list_iter_next(it);
	if (!file_tok)
		return (PARSER_SYNTAX_ERR);
	if (!*cmd)
	{
		*cmd = command_create(NULL);
		if (!*cmd)
			return (MS_ALLOCATION_ERR);
	}
	*cmd = handle_redirect(tok, file_tok, *cmd);
	if (!*cmd)
		return (PARSER_SYNTAX_ERR);
	return (MS_OK);
}

int	handle_word_or_arg(t_token *tok, t_command **cmd)
{
	if (!*cmd)
		*cmd = handle_command_token(tok, *cmd);
	else
		*cmd = handle_arg_token(tok, *cmd);
	if (!*cmd)
		return (PARSER_SYNTAX_ERR);
	return (MS_OK);
}

int	push_finished_cmd(t_command *cmd, t_gen_list *commands)
{
	if (!cmd)
		return (PARSER_SYNTAX_ERR);
	gen_list_push_back(commands, cmd);
	return (MS_OK);
}

bool	check_status_command_token(int status, t_command *cmd, t_token *tok)
{
	return ((status == MS_OK && !cmd && !lexer_is_token_type(tok, TOKEN_PIPE))
		|| lexer_is_token_type(tok, INVALID_OPERATOR));
}
