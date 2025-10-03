/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:07:34 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/03 16:26:22 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"


t_gen_list *parse_tokens_to_commands(t_gen_list *tokens)
{
    if (!tokens)
        return NULL;

    t_gen_list *commands = gen_list_create();
    if (!commands)
        return NULL;

    t_command *current_cmd = NULL;

    t_gen_list_iter *it = gen_list_iter_start(tokens);
    t_token *tok;

    while ((tok = (t_token *)gen_list_iter_next(it)) != NULL)
    {
        if (tok->type == TOKEN_CMD)
        {
            current_cmd = command_create(tok->value);
            if (!current_cmd)
                goto error;
            size_t len = ft_strlen(tok->value);
            char *arg_copy = malloc(len + 1);
            if (!arg_copy)
                goto error;
            ft_strlcpy(arg_copy, tok->value, len + 1);

            command_push_arg(current_cmd, arg_copy);
        }
        else if (tok->type == TOKEN_ARG)
        {
            if (!current_cmd)
                goto error;

            size_t len = ft_strlen(tok->value);
            char *arg_copy = malloc(len + 1);
            if (!arg_copy)
                goto error;
            ft_strlcpy(arg_copy, tok->value, len + 1);

            command_push_arg(current_cmd, arg_copy);
        }
        else if (tok->type == TOKEN_PIPE)
        {
            if (!current_cmd)
                goto error;

            gen_list_push_back(commands, current_cmd);
            current_cmd = NULL;
        }
        else if (tok->type == TOKEN_REDIR_IN ||
                 tok->type == TOKEN_REDIR_OUT ||
                 tok->type == TOKEN_REDIR_APPEND ||
                 tok->type == TOKEN_HEREDOC)
        {
            t_token *file_tok = (t_token *)gen_list_iter_next(it);
            if (!file_tok || file_tok->type != TOKEN_ARG || !current_cmd)
                goto error;

            t_redirect_type r_type = NONE;
            if (tok->type == TOKEN_REDIR_IN)
                r_type = LEFT_REDIRECT;
            else if (tok->type == TOKEN_REDIR_OUT)
                r_type = RIGHT_REDIRECT;
            else if (tok->type == TOKEN_REDIR_APPEND)
                r_type = DOUBLE_RIGHT_REDIRECT;
            else if (tok->type == TOKEN_HEREDOC)
                r_type = DOUBLE_LEFT_REDIRECT;

            command_push_redirect(current_cmd, r_type, file_tok->value);
        }
    }

    if (current_cmd)
        gen_list_push_back(commands, current_cmd);

    gen_list_iter_destroy(it);
    return commands;

error:
    if (current_cmd)
        command_destroy(current_cmd);
    gen_list_iter_destroy(it);
    gen_list_destroy(commands, (void (*)(void *))command_destroy);
    return NULL;
}


void print_commands(t_gen_list *commands) {
    if (!commands || gen_list_is_empty(commands)) {
        printf("No commands to print.\n");
        return;
    }

    t_gen_list_iter *it = gen_list_iter_start(commands);
    t_command *cmd;
    int index = 1;
    while ((cmd = (t_command *)gen_list_iter_next(it)) != NULL) {
        print_command(cmd, index++);
    }
}

t_gen_list *parse_line(char *line)
{
	t_gen_list	*tokens;
	t_gen_list *commands;
	
	tokens = lexer_tokenize(line);
	if(!tokens)
		return NULL;
	
	commands = parse_tokens_to_commands(tokens);
	if(!commands)
	{
		lexer_destroy(tokens);
		return (NULL);
	}
	lexer_destroy(tokens);
	return (commands);
}