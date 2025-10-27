/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:07:34 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/27 16:38:02 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"


int parse_tokens_to_commands(t_gen_list *tokens, t_gen_list *commands)
{
    if (!tokens)
        return PARSER_NULL_ERR;

    t_command *current_cmd = NULL;
    t_gen_list_iter *it = gen_list_iter_start(tokens);
    t_token *tok;
    while ((tok = (t_token *)gen_list_iter_next(it)) != NULL)
    {
        // Caso: encontramos un comando
        if (lexer_is_token_type(tok, TOKEN_CMD))
        {
            // Si aún no había comando, creamos uno
            if (!current_cmd)
            {
                current_cmd = command_create(ft_strdup(lexer_get_token_content(tok)));
                if (!current_cmd)
                    goto error;
            }
            // Añadimos como primer argumento el propio comando
            char *arg_copy = ft_strdup(lexer_get_token_content(tok));
            if (!arg_copy)
                goto error;
            command_push_arg(current_cmd, arg_copy);
        }
        // Caso: argumento normal
        else if (lexer_is_token_type(tok, TOKEN_ARG))
        {
            if (!current_cmd)
            {
                // bash trata un arg al inicio como comando implícito?
                current_cmd = command_create(NULL);
                if (!current_cmd)
                    goto error;
            }
            char *arg_copy = ft_strdup(lexer_get_token_content(tok));
            if (!arg_copy)
                goto error;
            command_push_arg(current_cmd, arg_copy);
        }
        // Caso: pipe -> cerramos comando actual y lo guardamos
        else if (lexer_is_token_type(tok,TOKEN_PIPE))
        {
            if (!current_cmd)
                goto error;

            gen_list_push_back(commands, current_cmd);
            current_cmd = NULL;
        }
        // Caso: redirect
        else if (lexer_is_token_type(tok, TOKEN_REDIR_IN)     ||
                 lexer_is_token_type(tok, TOKEN_REDIR_OUT)    ||
                 lexer_is_token_type(tok, TOKEN_REDIR_APPEND) ||
                 lexer_is_token_type(tok, TOKEN_HEREDOC))
        {
            // Si todavía no existe comando, creamos uno "vacío"
            if (!current_cmd)
            {
                current_cmd = command_create(NULL);
                if (!current_cmd)
                    goto error;
            }
            t_redirect_type r_type = NONE;
            if (lexer_is_token_type(tok, TOKEN_REDIR_IN))
                r_type = LEFT_REDIRECT;
            else if (lexer_is_token_type(tok, TOKEN_REDIR_OUT))
                r_type = RIGHT_REDIRECT;
            else if (lexer_is_token_type(tok, TOKEN_REDIR_APPEND))
                r_type = DOUBLE_RIGHT_REDIRECT;
            else if (lexer_is_token_type(tok, TOKEN_HEREDOC))
                r_type = DOUBLE_LEFT_REDIRECT;

            // mirar el siguiente token como target (puede ser NULL)
			t_token *file_tok = (t_token *)gen_list_iter_next(it);
            char *redir_target = NULL;
            if (file_tok && lexer_is_token_type(file_tok, TOKEN_ARG))
                redir_target = lexer_get_token_content(file_tok);
			if (!command_get_name(current_cmd))
			{
				char *name_aux = lexer_get_token_content((t_token *)gen_list_iter_next(it));
				t_command *new_cmd = command_create(name_aux);
				t_command *old_cmd = current_cmd;
				current_cmd = new_cmd;
				command_destroy(old_cmd);
				old_cmd = NULL;
				command_push_arg(current_cmd, name_aux);
				command_push_redirect(current_cmd, r_type, redir_target);
			}
			else
            	command_push_redirect(current_cmd, r_type, redir_target);
        }
    }

    if (current_cmd)
        gen_list_push_back(commands, current_cmd);
    gen_list_iter_destroy(it);
    return MS_OK;

error:
    if (current_cmd)
        command_destroy(current_cmd);
    gen_list_iter_destroy(it);
    gen_list_destroy(commands, (void (*)(void *))command_destroy);
    return PARSER_ERR;
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

int parse_line(char *line, t_gen_list *commands)
{
	int status_code;
	t_gen_list	*tokens;

	tokens = gen_list_create();
	if(!tokens)
		return MS_ALLOCATION_ERR;
	status_code = lexer_tokenize(line, tokens);
	if (status_code != MS_OK)
	{
		lexer_destroy(tokens);
		return (PARSER_ERR);
	}
	//print_tokens(tokens);
	status_code = parse_tokens_to_commands(tokens, commands);
	if (status_code != MS_OK)
	{
		lexer_destroy(tokens);
		return (PARSER_ERR);
	}
	lexer_destroy(tokens);
	//print_commands(commands);
	return (MS_OK);
}