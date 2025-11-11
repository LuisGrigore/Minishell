/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:31:53 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/11 15:27:03 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static void	noop_destroy(void *p)
{
	(void)p;
}

static bool	is_pipe_token(t_token *tok)
{
	if (!tok)
		return (false);
	if (lexer_is_token_type(tok, TOKEN_PIPE))
		return (true);
	return (false);
}

static bool	is_word_token(t_token *tok)
{
	if (!tok)
		return (false);
	if (lexer_is_token_type(tok, TOKEN_WORD))
		return (true);
	return (false);
}

static bool	is_redir_token(t_token *tok)
{
	if (!tok)
		return (false);
	return (lexer_is_token_type(tok, TOKEN_REDIR_IN) || lexer_is_token_type(tok,
			TOKEN_REDIR_OUT) || lexer_is_token_type(tok, TOKEN_REDIR_APPEND)
		|| lexer_is_token_type(tok, TOKEN_HEREDOC));
}

static int	handle_redir_wrapper(t_token *tok, t_gen_list_iter *it,
		t_command **cmd)
{
	t_token	*file_tok;

	file_tok = gen_list_iter_next(it);
	*cmd = handle_redirect(tok, file_tok, *cmd, it);
	if (!*cmd)
		return (PARSER_ERR);
	return (MS_OK);
}

static int	handle_word_or_arg(t_token *tok, t_command **cmd)
{
	if (!*cmd)
		*cmd = handle_command_token(tok, *cmd);
	else
		*cmd = handle_arg_token(tok, *cmd);
	if (!*cmd)
		return (PARSER_ERR);
	return (MS_OK);
}

static int	push_finished_cmd(t_command *cmd, t_gen_list *commands)
{
	if (!cmd)
		return PARSER_ERR;
	gen_list_push_back(commands, cmd);
	return MS_OK;
}

static int	process_token(t_token *tok, t_gen_list_iter *it,
		t_gen_list *commands, t_command **cmd)
{
	int	status;

	if (is_pipe_token(tok))
	{
		status = handle_pipe_token(*cmd, commands);
		if (!status)
			return PARSER_ERR;
		*cmd = NULL;
		return MS_OK;
	}
	if (is_word_token(tok))
		return handle_word_or_arg(tok, cmd);
	if (is_redir_token(tok))
		return handle_redir_wrapper(tok, it, cmd);
	return PARSER_ERR;
}

int	parse_command(t_gen_list *command_tokens, t_gen_list *commands)
{
	t_gen_list_iter	*it;
	t_token			*tok;
	t_command		*cmd;
	int				status;

	if (!command_tokens)
		return PARSER_ERR;
	it = gen_list_iter_start(command_tokens);
	if (!it)
		return MS_ALLOCATION_ERR;
	cmd = NULL;
	status = MS_OK;
	tok = gen_list_iter_next(it);
	while (tok && status == MS_OK)
	{
		status = process_token(tok, it, commands, &cmd);
		if (status == MS_OK && !cmd && !is_pipe_token(tok))
			status = PARSER_ERR;
		tok = gen_list_iter_next(it);
	}
	if (status == MS_OK && cmd)
		status = push_finished_cmd(cmd, commands);
	if (status != MS_OK && cmd)
		command_destroy(cmd);
	gen_list_iter_destroy(it);
	return status;
}

static int	flush_command_tokens(t_gen_list *current, t_gen_list *commands)
{
	int	status;

	if (gen_list_is_empty(current))
		return MS_OK;
	status = parse_command(current, commands);
	return status;
}

static int	add_token_to_current(t_gen_list *current, t_token *tok)
{
	gen_list_push_back(current, tok);
	return MS_OK;
}

static int	process_parser_token(t_token *tok, t_gen_list **current,
		t_gen_list *commands)
{
	int	status;

	if (is_pipe_token(tok))
	{
		status = flush_command_tokens(*current, commands);
		if (status != MS_OK)
			return status;
		gen_list_destroy(*current, noop_destroy);
		*current = gen_list_create();
		if (!*current)
			return MS_ALLOCATION_ERR;
		return MS_OK;
	}
	add_token_to_current(*current, tok);
	return MS_OK;
}

int	parser_aux(t_gen_list *tokens, t_gen_list *commands)
{
	t_gen_list_iter	*it;
	t_token			*tok;
	t_gen_list		*current;
	int				status;

	if (!tokens)
		return PARSER_ERR;
	it = gen_list_iter_start(tokens);
	if (!it)
		return MS_ALLOCATION_ERR;
	current = gen_list_create();
	if (!current)
	{
		gen_list_iter_destroy(it);
		return MS_ALLOCATION_ERR;
	}
	status = MS_OK;
	tok = gen_list_iter_next(it);
	while (tok && status == MS_OK)
	{
		status = process_parser_token(tok, &current, commands);
		tok = gen_list_iter_next(it);
	}
	if (status == MS_OK)
		status = flush_command_tokens(current, commands);
	gen_list_destroy(current, noop_destroy);
	gen_list_iter_destroy(it);
	return status;
}

int	parse_line(char *line, t_gen_list *commands, t_environment *env)
{
	t_gen_list	*tokens;
	int			status;

	tokens = gen_list_create();
	if (!tokens)
		return MS_ALLOCATION_ERR;
	status = tokenize_line(line, tokens, env);
	if (status != MS_OK)
	{
		lexer_destroy(tokens);
		return status;
	}
	status = parser_aux(tokens, commands);
	lexer_destroy(tokens);
	return status;
}
