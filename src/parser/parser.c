/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:31:53 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 04:22:58 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static void	parse_command_end(t_gen_list *commands, t_command *cmd, int *status)
{
	if (*status == MS_OK && cmd)
		*status = push_finished_cmd(cmd, commands);
	if (*status != MS_OK && cmd)
		command_destroy(cmd);
}

int	parse_command(t_gen_list *command_tokens, t_gen_list *commands)
{
	t_gen_list_iter	*it;
	t_token			*tok;
	t_command		*cmd;
	int				status;

	if (!command_tokens)
		return (PARSER_ERR);
	it = gen_list_iter_start(command_tokens);
	if (!it)
		return (MS_ALLOCATION_ERR);
	cmd = NULL;
	status = MS_OK;
	tok = gen_list_iter_next(it);
	while (tok && status == MS_OK)
	{
		status = process_token(tok, it, commands, &cmd);
		if ((status == MS_OK && !cmd && !lexer_is_token_type(tok, TOKEN_PIPE))
			|| lexer_is_token_type(tok, INVALID_OPERATOR))
			status = PARSER_SYNTAX_ERR;
		tok = gen_list_iter_next(it);
	}
	parse_command_end(commands, cmd, &status);
	return (gen_list_iter_destroy(it), status);
}

static t_gen_list	*get_current_command_tokens(t_gen_list *tokens)
{
	t_token		*current_token;
	t_gen_list	*current_command_tokens;
	t_gen_list	*discard_tokens;

	current_command_tokens = gen_list_create();
	discard_tokens = gen_list_create();
	if (!current_command_tokens)
		return (NULL);
	while (true)
	{
		current_token = (t_token *)gen_list_pop_front(tokens);
		if (!current_token)
			break ;
		if (lexer_is_token_type(current_token, TOKEN_PIPE))
		{
			gen_list_push_front(discard_tokens, current_token);
			break ;
		}
		gen_list_push_back(current_command_tokens, current_token);
	}
	lexer_destroy(discard_tokens);
	return (current_command_tokens);
}

static int	parser_aux(t_gen_list *tokens, t_gen_list *commands)
{
	t_gen_list	*current_command_tokens;
	int			status;

	if (gen_list_is_empty(tokens))
		return (MS_OK);
	current_command_tokens = get_current_command_tokens(tokens);
	if (!current_command_tokens)
		return (lexer_destroy(current_command_tokens), MS_ALLOCATION_ERR);
	if (gen_list_is_empty(current_command_tokens))
		return (lexer_destroy(current_command_tokens), PARSER_SYNTAX_ERR);
	status = parse_command(current_command_tokens, commands);
	if (status != MS_OK)
		return (lexer_destroy(current_command_tokens), status);
	return (lexer_destroy(current_command_tokens), parser_aux(tokens,
			commands));
}

int	parse_line(char *line, t_gen_list *commands, t_environment *env)
{
	t_gen_list	*tokens;
	int			status;

	tokens = gen_list_create();
	if (!tokens)
		return (MS_ALLOCATION_ERR);
	status = tokenize_line(line, tokens, env);
	if (status != MS_OK)
	{
		lexer_destroy(tokens);
		return (status);
	}
	status = parser_aux(tokens, commands);
	lexer_destroy(tokens);
	return (status);
}
