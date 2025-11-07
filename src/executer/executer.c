/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:15:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/07 18:08:25 by lgrigore         ###   ########.fr       */
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
        return(-1);

    pm = pipe_manager_init(n);
    if (!pm)
        return(-1);

    it = gen_list_iter_start(commands);
    if (!it)
        return (pipe_manager_destroy(pm), -1);

    pids = malloc(sizeof(pid_t) * n);
    if (!pids)
        return (gen_list_iter_destroy(it), pipe_manager_destroy(pm), -1);

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

    for (size_t j = 0; j < i; j++)
        waitpid(pids[j], exit_status, 0);

    gen_list_iter_destroy(it);
    free(pids);
    pipe_manager_destroy(pm);
	//Borra el archivo temporal despues de haber esperado a los procesos hijos
    unlink(PATH_HEREDOC_TEMP_FILE);
        return(0);
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
		if( status_code != MS_OK)
        {
            if(status_code != BINBUILTIN_SUCCESS)
                exit_status = 1;
			env_set_last_status_code(env, exit_status);
            gen_list_destroy(commands, command_destroy_data);
			if(status_code == BINBUILTIN_SUCCESS)
            	return(MS_OK);
			return(status_code);
        }
            
		return(MS_OK);
	}
	status_code = execute_commands_with_pipes(commands, mini_state, &exit_status);
	gen_list_destroy(commands, command_destroy_data);
    env_set_last_status_code(env, exit_status);
	return (status_code);
}
