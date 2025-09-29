/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:15:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/29 15:17:43 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fcntl.h"
# include "sys/wait.h"
# include "unistd.h"
#include "../libft/libft.h"
#include "readline/readline.h"
#include "../list/list.h"
#include "../include/command.h"

void execute_commands_with_pipes(t_gen_list *commands, t_gen_list *env)
{
    size_t n = commands->size;
    int (*pipes)[2] = malloc(sizeof(int[2]) * (n - 1));
    if (n > 1 && !pipes)
        return;

    for (size_t i = 0; i < n - 1; i++)
        pipe(pipes[i]);

    t_iter it = iter_start(commands);
    t_command *cmd;
    pid_t *pids = malloc(sizeof(pid_t) * n);
    size_t i = 0;

    while ((cmd = iter_next(&it)) != NULL)
    {
        if (cmd->command_funct == cd_execute ||
            cmd->command_funct == export_execute ||
            cmd->command_funct == unset_execute)
        {
            cmd->command_funct(cmd, env);
            i++;
            continue;
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            if (i > 0)
            {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }
            if (i < n - 1)
            {
                dup2(pipes[i][1], STDOUT_FILENO);
            }


            for (size_t j = 0; j < n - 1; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            cmd->command_funct(cmd, env);
            exit(0);
        }
        else
        {

            pids[i] = pid;
        }

        i++;
    }


    for (size_t j = 0; j < n - 1; j++)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }


    for (size_t j = 0; j < i; j++)
        waitpid(pids[j], NULL, 0);

    free(pids);
    if (pipes)
        free(pipes);
}