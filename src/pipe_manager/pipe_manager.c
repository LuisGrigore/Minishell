/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:42:28 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 00:19:19 by lgrigore         ###   ########.fr       */
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
