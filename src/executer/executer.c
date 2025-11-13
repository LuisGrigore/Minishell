/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:15:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 02:10:42 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_internal.h"

static void	command_destroy_data(void *command_ptr)
{
	command_destroy((t_command *)command_ptr);
}

static int	no_fork_command_rutine(t_gen_list *commands,
		t_mini_state *mini_state)
{
	int	status_code;

	status_code = command_exec((t_command *)gen_list_peek_top(commands),
			mini_state);
	destroy_temp_fles(mini_state);
	gen_list_destroy(commands, command_destroy_data);
	return (status_code);
}
int		fork_heredocs_create(t_gen_list *commands,t_mini_state *mini_state)
{
	pid_t pid;
	int		status_code;

	pid = fork();
	if(pid == 0)
		return(command_heredocs_create(commands, mini_state));
	waitpid(pid, &status_code, 0);
	if(status_code == MS_OK)
		status_code = command_heredocs_asignate(commands, mini_state);
	return(status_code);
}

int	execute_line(char *line, t_mini_state *mini_state)
{
	int				status_code;
	t_gen_list		*commands;
	int				exit_status;
	t_environment	*env;

	env = mini_state_get_environment(mini_state);
	exit_status = 0;
	commands = gen_list_create();
	if (!commands)
		return (MS_ALLOCATION_ERR);
	status_code = parse_line(line, commands, env);
	if (status_code != MS_OK)
		return (gen_list_destroy(commands, command_destroy_data), status_code);
	status_code = fork_heredocs_create(commands, mini_state);
	if (mini_state_get_exit_after_last_command(mini_state)|| status_code != MS_OK)
		return (gen_list_destroy(commands,	command_destroy_data), status_code);
	if (gen_list_get_size(commands) == 1
		&& command_is_built_in((t_command *)gen_list_peek_top(commands)))
		return (no_fork_command_rutine(commands, mini_state));
	status_code = execute_with_pipes(commands, mini_state, &exit_status);
	gen_list_destroy(commands, command_destroy_data);
	if (status_code == MS_OK)
		return (EXTERNALY_DEFINED_STATUS_CODE + exit_status);
	return (status_code);
}
