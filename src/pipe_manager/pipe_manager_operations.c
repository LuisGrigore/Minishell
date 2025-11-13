/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager_operations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:18:59 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 19:29:10 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_manager_internal.h"

int	pipe_manager_setup_command(t_pipe_manager *pm, size_t index)
{
	int	dup_ret;

	dup_ret = 0;
	if (!pm)
		return (PIPE_MANAGER_IS_NULL);
	if (pm->n_cmds <= 1)
		return (MS_OK);
	if (index > 0)
		dup_ret = dup2(pm->pipes[index - 1][0], STDIN_FILENO);
	if (dup_ret != -1 && index < pm->n_cmds - 1)
		dup_ret = dup2(pm->pipes[index][1], STDOUT_FILENO);
	if (dup_ret == -1)
		return (MS_DUP2_ERR);
	return (MS_OK);
}

int	pipe_manager_close_all(t_pipe_manager *pm)
{
	size_t	i;
	int		close_ret;
	int		error_flag;

	if (!pm)
		return (PIPE_MANAGER_IS_NULL);
	if (!pm->pipes)
		return (PIPE_MANAGER_MALFORMED);
	error_flag = 0;
	i = 0;
	while (i < pm->n_cmds - 1)
	{
		close_ret = close(pm->pipes[i][0]);
		if (close_ret == -1)
			error_flag = 1;
		close_ret = close(pm->pipes[i][1]);
		if (close_ret == -1)
			error_flag = 1;
		i++;
	}
	if (error_flag)
		return (MS_CLOSE_ERR);
	return (MS_OK);
}

void	pipe_manager_destroy(t_pipe_manager *pm)
{
	if (!pm)
		return ;
	free(pm->pipes);
	free(pm);
}
