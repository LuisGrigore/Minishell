/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:15:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/04 13:00:21 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_internal.h"

#include <stdio.h>


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
}

static void command_destroy_data(void *command_ptr)
{
	command_destroy((t_command *) command_ptr);
}

int execute_line(char *line, t_gen_list *env)
{
	t_gen_list *commands;

	commands = parse_line(line);
	if(!commands)
	//TODO :: crear codigos de error adecuados
		return(-1);
	if (gen_list_get_size(commands) == 1 && command_is_built_in((t_command *) gen_list_peek_top(commands)))
	{
		command_exec((t_command *) gen_list_peek_top(commands), env);
		return(0);
	}
	execute_commands_with_pipes(commands, env);
	gen_list_destroy(commands, command_destroy_data);
	return (0);
}
