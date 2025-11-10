/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:15:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/10 19:22:14 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_internal.h"


static void execute_end(t_pipe_manager *pm, pid_t *pids, size_t i, int *exit_status)
{
    size_t j;
    int tmp_status;
    
    j = 0;    
    pipe_manager_close_all(pm);
    while (j < i - 1)
    {
        waitpid(pids[j], &tmp_status, 0);
        j++;
    }
    waitpid(pids[i - 1], exit_status, 0);
    if (WIFEXITED(*exit_status))
        *exit_status = WEXITSTATUS(*exit_status);
    free(pids);
    pipe_manager_destroy(pm);
    unlink(PATH_HEREDOC_TEMP_FILE);
}
static int execute_init(t_gen_list *commands, t_pipe_manager **pm, t_gen_list_iter **it, pid_t **pids)
{
    size_t n;

    n = gen_list_get_size (commands);
    if (n == 0)
        return(MS_OK);
    *pm = pipe_manager_init(n);
    if (!pm)
        return(MS_ALLOCATION_ERR);
   *it = gen_list_iter_start(commands);
    if (*it == NULL)
        return (pipe_manager_destroy(*pm), MS_ALLOCATION_ERR);
    *pids = malloc(sizeof(pid_t) * n);
    if (*pids == NULL)
        return (gen_list_iter_destroy(*it), pipe_manager_destroy(*pm), MS_ALLOCATION_ERR);
    return(-1);
}
static int execute_fork_loop(pid_t *pids, t_gen_list_iter *it, t_mini_state *mini_state, t_pipe_manager *pm)
{
    t_command *cmd;
    int status_code;
    size_t i;
    
    i = 0;
     while ((cmd = gen_list_iter_next(it)) != NULL)
    {
        pids[i] = fork();
        if (pids[i] == 0) // hijo
        {
            pipe_manager_setup_command(pm, i);
            pipe_manager_close_all(pm);
            status_code = command_exec(cmd, mini_state);
			free(pids);
            gen_list_iter_destroy(it);
            pipe_manager_destroy((pm));
			mini_state_set_exit_after_last_command(mini_state, true);
			return(status_code);
        }
        i++;
    }
    return(-1);
}
//TODO :: hacer que devuelva int con error y tal
static  int execute_commands_with_pipes(t_gen_list *commands, t_mini_state *mini_state, int *exit_status)
{
    t_pipe_manager *pm = NULL;
    t_gen_list_iter *it;
    pid_t *pids;
    //size_t i = 0;
    int status_code;

    status_code = execute_init(commands, &pm, &it, &pids);
    if(status_code != -1)
        return(status_code);
    status_code = execute_fork_loop(pids, it, mini_state, pm);
    if(status_code != -1)
        return(status_code);
    execute_end(pm, pids, gen_list_get_size(commands), exit_status);
    gen_list_iter_destroy(it);
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
	t_environment *env;

	env = mini_state_get_environment(mini_state);
    exit_status = 0;
	commands = gen_list_create();
	if (!commands)
		return (MS_ALLOCATION_ERR);
    status_code = new_parse_line(line, commands, env);
	//print_command((t_command *)gen_list_pop_front(commands),0);
	if(status_code != MS_OK)
		return (status_code);
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
