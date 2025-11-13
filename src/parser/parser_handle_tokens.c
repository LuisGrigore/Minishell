/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:07:34 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 19:25:42 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

t_command	*handle_command_token(t_token *tok, t_command *current_cmd)
{
	char	*word;

	word = lexer_get_token_content(tok);
	if (!current_cmd)
	{
		current_cmd = command_create(word);
		if (!current_cmd)
			return (NULL);
		command_push_arg(current_cmd, word);
		return (current_cmd);
	}
	if (!command_get_name(current_cmd))
		command_set_name(current_cmd, word);
	else
		command_push_arg(current_cmd, word);
	return (current_cmd);
}

t_command	*handle_arg_token(t_token *tok, t_command *current_cmd)
{
	if (!current_cmd)
	{
		current_cmd = command_create(lexer_get_token_content(tok));
		if (!current_cmd)
			return (NULL);
	}
	else
	{
		if (!command_get_name(current_cmd))
			command_set_name(current_cmd, lexer_get_token_content(tok));
		else
			command_push_arg(current_cmd, lexer_get_token_content(tok));
	}
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
	return (DOUBLE_LEFT_REDIRECT);
}

t_command	*handle_redirect(t_token *tok, t_token *file_tok,
		t_command *current_cmd)
{
	t_redirect_type	r_type;
	char			*redir_target;

	if (!current_cmd)
	{
		current_cmd = command_create(NULL);
		if (!current_cmd)
			return (NULL);
	}
	r_type = get_redirect_type(tok);
	if (!(file_tok && lexer_is_token_type(file_tok, TOKEN_WORD)))
		return (NULL);
	redir_target = lexer_get_token_content(file_tok);
	command_push_redirect(current_cmd, r_type, redir_target);
	return (current_cmd);
}
