/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:07:34 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/07 00:19:37 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

t_command	*handle_command_token(t_token *tok, t_command *current_cmd)
{
	if (!current_cmd)
	{
		current_cmd = command_create(ft_strdup(lexer_get_token_content(tok)));
		if (!current_cmd)
			return (NULL);
	}
	command_push_arg(current_cmd, lexer_get_token_content(tok));
	return (current_cmd);
}

t_command	*handle_arg_token(t_token *tok, t_command *current_cmd)
{

	if (!current_cmd)
	{
		current_cmd = command_create(NULL);
		if (!current_cmd)
			return (NULL);
	}
	command_push_arg(current_cmd, lexer_get_token_content(tok));
	return (current_cmd);
}

int	handle_pipe_token(t_command *current_cmd, t_gen_list *commands)
{
	if (!current_cmd)
		return (0);
	gen_list_push_back(commands, current_cmd);
	return (1);
}

static t_redirect_type	get_redirect_type(t_token *tok)
{
	if (lexer_is_token_type(tok, TOKEN_REDIR_IN))
		return (LEFT_REDIRECT);
	if (lexer_is_token_type(tok, TOKEN_REDIR_OUT))
		return (RIGHT_REDIRECT);
	if (lexer_is_token_type(tok, TOKEN_REDIR_APPEND))
		return (DOUBLE_RIGHT_REDIRECT);
	if (lexer_is_token_type(tok, TOKEN_HEREDOC))
		return (DOUBLE_LEFT_REDIRECT);
	return (NONE);
}

t_command	*handle_redirect(t_token *tok, t_token *file_tok,
		t_command *current_cmd, t_gen_list_iter *it)
{
	t_redirect_type	r_type;
	char			*redir_target;
	t_command		*new_cmd;
	char			*name_aux;

	if (!current_cmd)
	{
		current_cmd = command_create(NULL);
		if (!current_cmd)
			return (NULL);
	}
	r_type = get_redirect_type(tok);
	redir_target = NULL;
	if (file_tok && lexer_is_token_type(file_tok, TOKEN_ARG))
		redir_target = lexer_get_token_content(file_tok);
	if (!command_get_name(current_cmd))
	{
		name_aux = lexer_get_token_content((t_token *)gen_list_iter_next(it));
		new_cmd = command_create(name_aux);
		command_destroy(current_cmd);
		current_cmd = new_cmd;
		command_push_arg(current_cmd, name_aux);
	}
	command_push_redirect(current_cmd, r_type, redir_target);
	return (current_cmd);
}
