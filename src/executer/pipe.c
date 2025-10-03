/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:15:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/03 16:57:40 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fcntl.h"
# include "sys/wait.h"
# include "unistd.h"
#include "../external/libft/libft.h"
#include "readline/readline.h"
# include "../external/gen_list/gen_list.h"
#include "../include/command.h"
#include "../include/executer.h"


void execute_commands_with_pipes(t_gen_list *commands, t_gen_list *env)
{
    size_t n = gen_list_get_size(commands);
    int (*pipes)[2] = NULL;
    t_gen_list_iter *it;
    t_command *cmd;
    pid_t *pids;
    size_t i = 0;

    if (n > 1)
    {
        pipes = malloc(sizeof(int[2]) * (n - 1));
        if (!pipes)
            return;
        for (size_t j = 0; j < n - 1; j++)
            if (pipe(pipes[j]) == -1)
                return (free(pipes), (void)0);
    }

    it = gen_list_iter_start(commands);
    if (!it)
        return (free(pipes), (void)0);

    pids = malloc(sizeof(pid_t) * n);
    if (!pids)
        return (gen_list_iter_destroy(it), free(pipes), (void)0);

    while ((cmd = gen_list_iter_next(it)) != NULL)
    {
        pid_t pid = fork();
        if (pid == 0) // hijo
        {
            if (i > 0)
                dup2(pipes[i - 1][0], STDIN_FILENO);
            if (i < n - 1)
                dup2(pipes[i][1], STDOUT_FILENO);

            // cerrar todos los pipes en el hijo
            for (size_t j = 0; j < n - 1; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // ejecutar comando con la nueva interfaz
            if (command_exec(cmd, env) == -1)
                exit(1);
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

    gen_list_iter_destroy(it);
    free(pids);
    free(pipes);
}
