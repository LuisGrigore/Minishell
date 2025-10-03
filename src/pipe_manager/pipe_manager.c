/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:42:28 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/03 19:21:45 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_manager_internal.h"

t_pipe_manager *pipe_manager_init(size_t n_cmds)
{
    t_pipe_manager *pm = malloc(sizeof(t_pipe_manager));
    if (!pm)
        return NULL;

    pm->n_cmds = n_cmds;
    pm->pipes = NULL;

    if (n_cmds > 1)
    {
        pm->pipes = malloc(sizeof(int[2]) * (n_cmds - 1));
        if (!pm->pipes)
        {
            free(pm);
            return NULL;
        }

        for (size_t j = 0; j < n_cmds - 1; j++)
        {
            if (pipe(pm->pipes[j]) == -1)
            {
                for (size_t k = 0; k < j; k++)
                {
                    close(pm->pipes[k][0]);
                    close(pm->pipes[k][1]);
                }
                free(pm->pipes);
                free(pm);
                return NULL;
            }
        }
    }

    return pm;
}

void pipe_manager_destroy(t_pipe_manager *pm)
{
    if (!pm)
        return;
    free(pm->pipes);
    free(pm);
}

void pipe_manager_setup_command(t_pipe_manager *pm, size_t index)
{
    if (!pm || pm->n_cmds <= 1)
        return;

    if (index > 0)
        dup2(pm->pipes[index - 1][0], STDIN_FILENO);
    if (index < pm->n_cmds - 1)
        dup2(pm->pipes[index][1], STDOUT_FILENO);
}

void pipe_manager_close_all(t_pipe_manager *pm)
{
    if (!pm || !pm->pipes)
        return;

    for (size_t j = 0; j < pm->n_cmds - 1; j++)
    {
        close(pm->pipes[j][0]);
        close(pm->pipes[j][1]);
    }
}