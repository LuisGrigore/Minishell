/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 04:14:11 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 04:16:59 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static int	handle_redir_wrapper(t_token *tok, t_gen_list_iter *it,
		t_command **cmd)
{
	t_token	*file_tok;

	file_tok = gen_list_iter_next(it);
	*cmd = handle_redirect(tok, file_tok, *cmd);
	if (!*cmd)
		return (PARSER_SYNTAX_ERR);
	return (MS_OK);
}

static int	handle_word_or_arg(t_token *tok, t_command **cmd)
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

int	process_token(t_token *tok, t_gen_list_iter *it, t_gen_list *commands,
		t_command **cmd)
{
	int	status;

	if (lexer_is_token_type(tok, TOKEN_PIPE))
	{
		status = handle_pipe_token(*cmd, commands);
		if (!status)
			return (PARSER_ERR);
		*cmd = NULL;
		return (MS_OK);
	}
	if (lexer_is_token_type(tok, TOKEN_WORD))
		return (handle_word_or_arg(tok, cmd));
	if (lexer_is_token_type(tok, TOKEN_REDIR_IN) || lexer_is_token_type(tok,
			TOKEN_REDIR_OUT) || lexer_is_token_type(tok, TOKEN_REDIR_APPEND)
		|| lexer_is_token_type(tok, TOKEN_HEREDOC))
		return (handle_redir_wrapper(tok, it, cmd));
	return (PARSER_ERR);
}
