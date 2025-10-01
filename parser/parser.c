/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:07:34 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/01 14:34:06 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static t_command_funct get_command_function(t_gen_list *args)
{
    t_gen_list_iter *it;
    char *cmd_name;

    if (!args || gen_list_is_empty(args))
        return NULL;
    it = gen_list_iter_start(args);
    if (!it)
        return NULL;
    cmd_name = gen_list_iter_next(it);
    gen_list_iter_destroy(it);
    if (!cmd_name || ft_strlen(cmd_name) == 0)
        return NULL;
    if (ft_strncmp(cmd_name, "echo", 5) == 0)
        return echo_execute;
    else if (ft_strncmp(cmd_name, "cd", 3) == 0)
        return cd_execute;
    else if (ft_strncmp(cmd_name, "pwd", 4) == 0)
        return pwd_execute;
    else if (ft_strncmp(cmd_name, "export", 7) == 0)
        return export_execute;
    else if (ft_strncmp(cmd_name, "unset", 6) == 0)
        return unset_execute;
    else if (ft_strncmp(cmd_name, "env", 4) == 0)
        return env_execute;
    else
        return bin_execute;
}

t_gen_list *parse_tokens_to_commands(t_gen_list *tokens)
{
    if (!tokens)
        return NULL;

    t_gen_list *commands = gen_list_create();
    if (!commands)
        return NULL;

    t_gen_list *current_args = gen_list_create();
    t_gen_list *current_redirects = gen_list_create();

    t_gen_list_iter *it = gen_list_iter_start(tokens);
    t_token *tok;

    while ((tok = (t_token *)gen_list_iter_next(it)) != NULL)
    {
        if (tok->type == TOKEN_ARG || tok->type == TOKEN_CMD)
        {
            // Copiar string y añadir a args usando ft_strlcpy
            size_t len = ft_strlen(tok->value);
            char *arg_copy = malloc(len + 1);
            if (!arg_copy)
                goto error;
            ft_strlcpy(arg_copy, tok->value, len + 1);
            gen_list_push_back(current_args, arg_copy);
        }
        else if (tok->type == TOKEN_PIPE)
        {
            // Asignar función antes de crear el comando
            t_command_funct funct = get_command_function(current_args);

            t_command *cmd = init_command(current_args, funct, current_redirects);
            if (!cmd)
                goto error;
            gen_list_push_back(commands, cmd);

            // Inicializar listas para siguiente comando
            current_args = gen_list_create();
            current_redirects = gen_list_create();
        }
        else if (tok->type == TOKEN_REDIR_IN ||
                 tok->type == TOKEN_REDIR_OUT ||
                 tok->type == TOKEN_REDIR_APPEND ||
                 tok->type == TOKEN_HEREDOC)
        {
            // El siguiente token debe ser el archivo
            t_token *file_tok = (t_token *)gen_list_iter_next(it);
            if (!file_tok || file_tok->type != TOKEN_ARG)
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

            t_redirect *redir = init_redirect(file_tok->value, r_type);
            if (!redir)
                goto error;
            gen_list_push_back(current_redirects, redir);
        }
    }

    // Guardar el último comando si hay args o redirs
    if (gen_list_is_empty(current_args) || gen_list_is_empty(current_redirects))
    {
        t_command_funct funct = get_command_function(current_args);
        t_command *cmd = init_command(current_args, funct, current_redirects);
        if (!cmd)
            goto error;
        gen_list_push_back(commands, cmd);
    }
    else
    {
        gen_list_destroy(current_args, free);
        gen_list_destroy(current_redirects, (void (*)(void *))destroy_command);
    }

	gen_list_iter_destroy(it);
    return commands;

error:
	gen_list_iter_destroy(it);
    gen_list_destroy(current_args, free);
    gen_list_destroy(current_redirects, (void (*)(void *))destroy_command);
    gen_list_destroy(commands, (void (*)(void *))destroy_command);
    return NULL;
}

void destroy_token_data(void *token_ptr)
{
	destroy_token((t_token *) token_ptr);
}

t_gen_list *parse_line(char *line)
{
	t_gen_list	*tokens;
	t_gen_list *commands;
	
	tokens = tokenize(line);
	if(!tokens)
		return NULL;
	
	commands = parse_tokens_to_commands(tokens);
	if(!commands)
	{
		gen_list_destroy(tokens, destroy_token_data);
		return (NULL);
	}
	gen_list_destroy(tokens, destroy_token_data);
	return (commands);
}