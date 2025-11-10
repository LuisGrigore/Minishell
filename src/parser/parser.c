/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:07:34 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/10 17:35:45 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static int	process_token(t_token *tok, t_command **current_cmd,
		t_gen_list *commands, t_gen_list_iter *it)
{
	t_token	*file_tok;

	if (lexer_is_token_type(tok, TOKEN_PIPE))
	{
		if (!handle_pipe_token(*current_cmd, commands))
			return (0);
		*current_cmd = NULL;
		return (1);
	}
	if (lexer_is_token_type(tok, TOKEN_WORD))
	{
		if (!*current_cmd)
			*current_cmd = handle_command_token(tok, *current_cmd);
		else
			*current_cmd = handle_arg_token(tok, *current_cmd);
	}
	else if (lexer_is_token_type(tok, TOKEN_REDIR_IN)
		|| lexer_is_token_type(tok, TOKEN_REDIR_OUT) || lexer_is_token_type(tok,
			TOKEN_REDIR_APPEND) || lexer_is_token_type(tok, TOKEN_HEREDOC))
	{
		file_tok = (t_token *)gen_list_iter_next(it);
		*current_cmd = handle_redirect(tok, file_tok, *current_cmd, it);
	}
	if (!*current_cmd && !lexer_is_token_type(tok, TOKEN_PIPE))
		return (0);
	return (1);
}

static int	process_tokens(t_gen_list_iter *it, t_command **cmd,
		t_gen_list *commands)
{
	t_token	*tok;
	int		status;

	status = MS_OK;
	tok = (t_token *)gen_list_iter_next(it);
	while (tok != NULL)
	{
		if (!process_token(tok, cmd, commands, it))
		{
			status = PARSER_ERR;
			break ;
		}
		tok = (t_token *)gen_list_iter_next(it);
	}
	return (status);
}

static int	finalize_parsing(t_command *cmd, t_gen_list_iter *it,
		t_gen_list *commands, int status)
{
	if (status == MS_OK && cmd)
		gen_list_push_back(commands, cmd);
	else if (status != MS_OK)
	{
		if (cmd)
			command_destroy(cmd);
		if (it)
			gen_list_iter_destroy(it);
		if (commands)
			gen_list_destroy(commands, (void (*)(void *))command_destroy);
		return (PARSER_ERR);
	}
	gen_list_iter_destroy(it);
	return (status);
}

int	parse_tokens_to_commands(t_gen_list *tokens, t_gen_list *commands)
{
	t_command		*current_cmd;
	t_gen_list_iter	*it;
	int				status;

	if (!tokens)
		return (PARSER_NULL_ERR);
	current_cmd = NULL;
	it = gen_list_iter_start(tokens);
	status = process_tokens(it, &current_cmd, commands);
	return (finalize_parsing(current_cmd, it, commands, status));
}

int	parse_line(char *line, t_gen_list *commands, t_environment *env)
{
	int			status_code;
	t_gen_list	*tokens;

	tokens = gen_list_create();
	if (!tokens)
		return (MS_ALLOCATION_ERR);
	// status_code = lexer_tokenize(line, tokens, env);
	status_code = new_tokenize_line(line, tokens, env);
	print_tokens(tokens);
	// if (status_code != MS_OK)
	// {
	// 	lexer_destroy(tokens);
	// 	return (PARSER_ERR);
	// }
	// status_code = parse_tokens_to_commands(tokens, commands);
	// if (status_code != MS_OK)
	// {
	// 	lexer_destroy(tokens);
	// 	return (PARSER_ERR);
	// }
	// lexer_destroy(tokens);
	return (MS_OK);
}
