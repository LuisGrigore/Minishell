/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:15:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/19 18:56:40 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_internal.h"

//TODO :: hacer que devuelva int con error y tal
static void execute_commands_with_pipes(t_gen_list *commands, t_gen_list *env)
{
    size_t n = gen_list_get_size(commands);
    t_pipe_manager *pm = NULL;
    t_gen_list_iter *it;
    t_command *cmd;
    pid_t *pids;
    size_t i = 0;

    if (n == 0)
        return;

    pm = pipe_manager_init(n);
    if (!pm)
        return;

    it = gen_list_iter_start(commands);
    if (!it)
        return (pipe_manager_destroy(pm), (void)0);

    pids = malloc(sizeof(pid_t) * n);
    if (!pids)
        return (gen_list_iter_destroy(it), pipe_manager_destroy(pm), (void)0);

    while ((cmd = gen_list_iter_next(it)) != NULL)
    {
        pid_t pid = fork();
        if (pid == 0) // hijo
        {
            pipe_manager_setup_command(pm, i);
            pipe_manager_close_all(pm);

            if (command_exec(cmd, env) == -1)
                exit(1);
            exit(0);
        }
        else
        {
            pids[i] = pid;
        }
        i++;
    }

    pipe_manager_close_all(pm);

    for (size_t j = 0; j < i; j++)
        waitpid(pids[j], NULL, 0);

    gen_list_iter_destroy(it);
    free(pids);
    pipe_manager_destroy(pm);
	//Borra el archivo temporal despues de haber esperado a los procesos hijos
    unlink(PATH_HEREDOC_TEMP_FILE);
}

static void command_destroy_data(void *command_ptr)
{
	command_destroy((t_command *) command_ptr);
}

static int handle_parser_errors(int status_code)
{
	return(MS_OK);
}

int execute_line(char *line, t_gen_list *env)
{
	int status_code;
	t_gen_list *commands;

	commands = gen_list_create();
	if (!commands)
		return (MS_ALLOCATION_ERR);
	status_code = parse_line(line, commands);
	if(status_code != MS_OK)
		return (EXECUTER_ERR);
	if (gen_list_get_size(commands) == 1 && command_is_built_in((t_command *) gen_list_peek_top(commands)))
	{
		command_exec((t_command *) gen_list_peek_top(commands), env);
		return(MS_OK);
	}
	execute_commands_with_pipes(commands, env);
	gen_list_destroy(commands, command_destroy_data);
	return (MS_OK);
}
