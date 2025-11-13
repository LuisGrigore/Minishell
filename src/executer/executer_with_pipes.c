/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_with_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:48:22 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 13:54:22 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_internal.h"

static void	execute_end(t_pipe_manager *pm, pid_t *pids, size_t i,
		int *exit_status)
{
	size_t	j;
	int		tmp_status;

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
}

static int	execute_init(t_gen_list *commands, t_pipe_manager **pm,
		t_gen_list_iter **it, pid_t **pids)
{
	size_t	n;

	n = gen_list_get_size(commands);
	if (n == 0)
		return (MS_OK);
	*pm = pipe_manager_init(n);
	if (!pm)
		return (MS_ALLOCATION_ERR);
	*it = gen_list_iter_start(commands);
	if (*it == NULL)
		return (pipe_manager_destroy(*pm), MS_ALLOCATION_ERR);
	*pids = malloc(sizeof(pid_t) * n);
	if (*pids == NULL)
		return (gen_list_iter_destroy(*it), pipe_manager_destroy(*pm),
			MS_ALLOCATION_ERR);
	return (-1);
}

static int	execute_fork_loop(pid_t *pids, t_gen_list_iter *it,
		t_mini_state *mini_state, t_pipe_manager *pm)
{
	t_command	*cmd;
	int			status_code;
	size_t		i;

	i = 0;
	cmd = gen_list_iter_next(it);
	if(!cmd)
		return (MS_ALLOCATION_ERR);
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			pipe_manager_setup_command(pm, i);
			pipe_manager_close_all(pm);
			status_code = command_exec(cmd, mini_state);
			free(pids);
			gen_list_iter_destroy(it);
			pipe_manager_destroy((pm));
			mini_state_set_exit_after_last_command(mini_state, true);
			return (status_code);
		}
		i++;
		cmd = gen_list_iter_next(it);
	}
	return (-1);
}
			// if (!command_get_args(cmd) || gen_list_is_empty(command_get_args(cmd)))
			// {
			// 	free(pids);
			// 	gen_list_iter_destroy(it);
			// 	pipe_manager_destroy((pm));
			// 	mini_state_set_exit_after_last_command(mini_state, true);
			// 	return (MS_OK);
			// }
			// else
			// {
			// 	status_code = command_exec(cmd, mini_state);
			// 	free(pids);
			// 	gen_list_iter_destroy(it);
			// 	pipe_manager_destroy((pm));
			// 	mini_state_set_exit_after_last_command(mini_state, true);
			// 	return (status_code);
			// }

int	execute_with_pipes(t_gen_list *commands, t_mini_state *mini_state,
		int *exit_status)
{
	t_pipe_manager	*pm;
	t_gen_list_iter	*it;
	pid_t			*pids;
	int				status_code;

	pm = NULL;
	status_code = execute_init(commands, &pm, &it, &pids);
	if (status_code != -1)
		return (status_code);
	status_code = execute_fork_loop(pids, it, mini_state, pm);
	if (status_code != -1)
		return (status_code);
	execute_end(pm, pids, gen_list_get_size(commands), exit_status);
	destroy_temp_fles(mini_state);
	gen_list_iter_destroy(it);
	return (MS_OK);
}
