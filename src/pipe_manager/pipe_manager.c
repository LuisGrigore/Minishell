/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:42:28 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/06 23:57:04 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_manager_internal.h"

static void	cleanup_pipes(t_pipe_manager *pm, size_t pipes_created)
{
	size_t	k;

	k = 0;
	while (k < pipes_created)
	{
		close(pm->pipes[k][0]);
		close(pm->pipes[k][1]);
		k++;
	}
	free(pm->pipes);
	free(pm);
}

static t_pipe_manager	*create_pipes(t_pipe_manager *pm, size_t n_cmds)
{
	size_t	j;

	pm->pipes = malloc(sizeof(int[2]) * (n_cmds - 1));
	if (!pm->pipes)
	{
		free(pm);
		return (NULL);
	}
	j = 0;
	while (j < n_cmds - 1)
	{
		if (pipe(pm->pipes[j]) == -1)
		{
			cleanup_pipes(pm, j);
			return (NULL);
		}
		j++;
	}
	return (pm);
}

t_pipe_manager	*pipe_manager_init(size_t n_cmds)
{
	t_pipe_manager	*pm;

	pm = malloc(sizeof(t_pipe_manager));
	if (!pm)
		return (NULL);
	pm->n_cmds = n_cmds;
	pm->pipes = NULL;
	if (n_cmds > 1)
		pm = create_pipes(pm, n_cmds);
	return (pm);
}

void	pipe_manager_destroy(t_pipe_manager *pm)
{
	if (!pm)
		return ;
	free(pm->pipes);
	free(pm);
}

int	pipe_manager_setup_command(t_pipe_manager *pm, size_t index)
{
	int	dup_ret;

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
