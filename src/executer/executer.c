/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:15:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/07 20:37:43 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_internal.h"

//TODO :: hacer que devuelva int con error y tal
static  int execute_commands_with_pipes(t_gen_list *commands, t_mini_state *mini_state, int *exit_status)
{
    size_t n = gen_list_get_size(commands);
    t_pipe_manager *pm = NULL;
    t_gen_list_iter *it;
    t_command *cmd;
    pid_t *pids;
    size_t i = 0;
    int status_code;

    if (n == 0)
        return(MS_OK);

    pm = pipe_manager_init(n);
    if (!pm)
        return(MS_ALLOCATION_ERR);

    it = gen_list_iter_start(commands);
    if (!it)
        return (pipe_manager_destroy(pm), MS_ALLOCATION_ERR);

    pids = malloc(sizeof(pid_t) * n);
    if (!pids)
        return (gen_list_iter_destroy(it), pipe_manager_destroy(pm), MS_ALLOCATION_ERR);

    while ((cmd = gen_list_iter_next(it)) != NULL)
    {
        pid_t pid = fork();
        if (pid == 0) // hijo
        {
            pipe_manager_setup_command(pm, i);
            pipe_manager_close_all(pm);
            status_code = command_exec(cmd, mini_state);
            if (status_code != MS_OK)
            {
                free(pids);
                gen_list_iter_destroy(it);
                pipe_manager_destroy((pm));
                return(status_code);
            }
            exit(0);
        }
        else
        {
            pids[i] = pid;
        }
        i++;
    }

    pipe_manager_close_all(pm);

    // Esperar a todos los procesos excepto el último
    for (size_t j = 0; j < i - 1; j++)
    {
        int tmp_status;
        waitpid(pids[j], &tmp_status, 0);
    }
    // Esperar al último proceso y guardar su estado
    waitpid(pids[i - 1], exit_status, 0);
    if (WIFEXITED(*exit_status))
        *exit_status = WEXITSTATUS(*exit_status);

    gen_list_iter_destroy(it);
    free(pids);
    pipe_manager_destroy(pm);
    unlink(PATH_HEREDOC_TEMP_FILE);
    return(MS_OK);
}

static void command_destroy_data(void *command_ptr)
{
	command_destroy((t_command *) command_ptr);
}


int execute_line(char *line, t_mini_state *mini_state)
{
	int status_code;
	t_gen_list *commands;
    int exit_status;
	t_gen_list *env;

	env = mini_state_get_environment_vars(mini_state);
    exit_status = 0;
	commands = gen_list_create();
	if (!commands)
		return (MS_ALLOCATION_ERR);
    status_code = parse_line(line, commands, env);
	if(status_code != MS_OK)
		return (EXECUTER_ERR);
	if (gen_list_get_size(commands) == 1 && command_is_built_in((t_command *) gen_list_peek_top(commands)))
	{   
        status_code = command_exec((t_command *) gen_list_peek_top(commands), mini_state);
		gen_list_destroy(commands, command_destroy_data);
		return (status_code);

	}
	status_code = execute_commands_with_pipes(commands, mini_state, &exit_status);
	gen_list_destroy(commands, command_destroy_data);
	if (status_code == MS_OK)
		return (EXTERNALY_DEFINED_STATUS_CODE + exit_status);
	return (status_code);
}
