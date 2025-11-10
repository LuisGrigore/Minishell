/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:31:53 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/10 16:15:52 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

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
static void	noop_destroy(void *p)
{
	(void)p;
}

/*
 * Minimal, list-based command parser implementation.
 * This reuses the helper functions declared in parser_internal.h
 * (handle_command_token, handle_arg_token, handle_redirect and
 * handle_pipe_token) by iterating over a token list using the
 * provided iterator API.
 */
int	parse_command(t_gen_list *command_tokens, t_gen_list *commands)
{
	t_gen_list_iter	*it;
	t_token			*tok;
	t_command		*current_cmd;
	int			status;

	if (!command_tokens)
		return (PARSER_ERR);
	it = gen_list_iter_start(command_tokens);
	if (!it)
		return (MS_ALLOCATION_ERR);
	current_cmd = NULL;
	status = MS_OK;
	tok = (t_token *)gen_list_iter_next(it);
	while (tok != NULL)
	{
		if (lexer_is_token_type(tok, TOKEN_PIPE))
		{
			if (!handle_pipe_token(current_cmd, commands))
			{
				status = PARSER_ERR;
				break ;
			}
			current_cmd = NULL;
		}
		else if (lexer_is_token_type(tok, TOKEN_WORD))
		{
			if (!current_cmd)
				current_cmd = handle_command_token(tok, current_cmd);
			else
				current_cmd = handle_arg_token(tok, current_cmd);
		}
		else if (lexer_is_token_type(tok, TOKEN_REDIR_IN)
			|| lexer_is_token_type(tok, TOKEN_REDIR_OUT)
			|| lexer_is_token_type(tok, TOKEN_REDIR_APPEND)
			|| lexer_is_token_type(tok, TOKEN_HEREDOC))
		{
			t_token *file_tok;

			file_tok = (t_token *)gen_list_iter_next(it);
			current_cmd = handle_redirect(tok, file_tok, current_cmd, it);
		}
		if (!current_cmd && !lexer_is_token_type(tok, TOKEN_PIPE))
		{
			status = PARSER_ERR;
			break ;
		}
		tok = (t_token *)gen_list_iter_next(it);
	}
	if (status == MS_OK && current_cmd)
		gen_list_push_back(commands, current_cmd);
	else if (status != MS_OK)
	{
		if (current_cmd)
			command_destroy(current_cmd);
		gen_list_iter_destroy(it);
		return (PARSER_ERR);
	}
	gen_list_iter_destroy(it);
	return (status);
}

int	parser_aux(t_gen_list *tokens, t_gen_list *commands)
{
	t_gen_list_iter *it;
	t_token *tok;
	t_gen_list *current_command_tokens;
	int status;

	if (!tokens)
		return (PARSER_ERR);
	it = gen_list_iter_start(tokens);
	if (!it)
		return (MS_ALLOCATION_ERR);
	current_command_tokens = gen_list_create();
	if (!current_command_tokens)
	{
		gen_list_iter_destroy(it);
		return (MS_ALLOCATION_ERR);
	}
	status = MS_OK;
	tok = (t_token *)gen_list_iter_next(it);
	while (tok != NULL)
	{
		if (lexer_is_token_type(tok, TOKEN_PIPE))
		{
			status = parse_command(current_command_tokens, commands);
			if (status != MS_OK)
			{
				gen_list_destroy(current_command_tokens, noop_destroy);
				gen_list_iter_destroy(it);
				return (status);
			}
			gen_list_destroy(current_command_tokens, noop_destroy);
			current_command_tokens = gen_list_create();
			if (!current_command_tokens)
			{
				gen_list_iter_destroy(it);
				return (MS_ALLOCATION_ERR);
			}
		}
		else
		{
			gen_list_push_back(current_command_tokens, tok);
		}
		tok = (t_token *)gen_list_iter_next(it);
	}
	/* final command (if any tokens collected) */
	if (!gen_list_is_empty(current_command_tokens))
	{
		status = parse_command(current_command_tokens, commands);
		if (status != MS_OK)
		{
			gen_list_destroy(current_command_tokens, noop_destroy);
			gen_list_iter_destroy(it);
			return (status);
		}
	}
	gen_list_destroy(current_command_tokens, noop_destroy);
	gen_list_iter_destroy(it);
	return (MS_OK);
}

int new_parse_line (char *line, t_gen_list *commands, t_environment *env)
{
	int			status_code;
	t_gen_list	*tokens;

	tokens = gen_list_create();
	if (!tokens)
		return (MS_ALLOCATION_ERR);
	// status_code = lexer_tokenize(line, tokens, env);
	status_code = new_tokenize_line(line, tokens, env);
	//print_tokens(tokens);
	if (status_code != MS_OK)
	{
		lexer_destroy(tokens);
		return (status_code);
	}
	status_code = parser_aux(tokens, commands);
	if (status_code != MS_OK)
	{
		lexer_destroy(tokens);
		return (status_code);
	}
	lexer_destroy(tokens);
	return (MS_OK);
}