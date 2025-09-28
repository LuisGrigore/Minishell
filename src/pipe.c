/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:15:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/28 23:20:08 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipe.h"
#include "../libft/libft.h"
#include "readline/readline.h"

static void	children(int pipes[][2], t_command *command,
				t_gen_list *envioroment, int actua_pipe);
static void	partent(int pipes[][2], t_command *command, t_gen_list *envioroment,
				int actua_pipe);
static int	cmd_env_change(char *command_name);
static int	auxiliar_backup(char *cmd, int std);
static void	close_pipes(int pipes[][2], size_t size, int actua_pipe);

void	command_execution(t_gen_list *command, t_gen_list *envioroment)
{
	int			pipes[command->size][2];
	t_node		*current_command_node;
	pid_t		check[command->size];
	int			i;
	t_command	*current_command;

	pipes[command->size - 1][0] = 0;
	i = 0;
	current_command_node = command->head;
	pipe(pipes[i]);
	while (current_command_node->next != NULL)
	{
		pipe(pipes[i + 1]);
		current_command = (t_command *)current_command_node->value;
		if (cmd_env_change((char *)current_command->args->head->value) == 0)
			check[i] = fork();
		else
		{
			children(pipes, current_command, envioroment, i);
			current_command_node = current_command_node->next;
			i++;
			continue ;
		}
		if (check[i] == 0)
		{
			close_pipes(pipes, command->size, i);
			children(pipes, current_command, envioroment, i);
		}
		current_command_node = current_command_node->next;
		i++;
	}
	current_command = (t_command *)current_command_node->value;
	if (cmd_env_change((char *)current_command->args->head->value) == 0)
		check[i] = fork();
	else
	{
		partent(pipes, current_command, envioroment, i);
		return ;
	}
	if (check[i] == 0)
	{
		close_pipes(pipes, command->size, i);
		partent(pipes, current_command, envioroment, i);
	}
	while (i >= 0)
	{
		if (check[i] != 0)
			waitpid(check[i], NULL, 0);
		i--;
	}
	close_pipes(pipes, command->size, i);
}
static void	children(int pipes[][2], t_command *command,
		t_gen_list *envioroment, int actua_pipe)
{
	int	back_up;

	/*int	fd;
	if(ok == 2)
		fd = open(argv[1], 0);
	else
		fd = STDIN_FILENO;*/
	/*if (fd == -1)
	{
		close(pipes[0]);
		close(pipes[1]);
		error_manager(NULL, "Check the privilegies of the  input file", 0);
	}*/
	back_up = auxiliar_backup((char *)command->args->head->value, STDIN_FILENO);
	dup2(pipes[actua_pipe][0], 0);
	dup2(pipes[actua_pipe + 1][1], 1);
	/*close(fd);*/
	if (back_up != 0)
	{
		close(pipes[actua_pipe][1]);
		close(pipes[actua_pipe + 1][0]);
	}
	command->command_funct(command, envioroment);
	if (back_up != 0)
		dup2(back_up, 0);
}
static void	partent(int pipes[][2], t_command *command, t_gen_list *envioroment,
		int actua_pipe)
{
	int	back_up;

	/*int	fd;*/
	/*if(ok == 2)
		fd = open(argv[1], 0);
	else
		fd = STDIN_FILENO;*/
	/*if (fd == -1)
	{
		close(pipes[0]);
		close(pipes[1]);
		error_manager(NULL, "Check the privilegies of the  input file", 0);
	}*/
	back_up = auxiliar_backup((char *)command->args->head->value, STDIN_FILENO);
	dup2(pipes[actua_pipe][0], 0);
	/*close(fd);*/
	if (back_up == 0)
		close(pipes[actua_pipe][0]);
	close(pipes[actua_pipe][1]);
	command->command_funct(command, envioroment);
}
static int	cmd_env_change(char *command_name)
{
	size_t	len;

	len = ft_strlen(command_name);
	if (ft_strncmp(command_name, "cd", len) == 0)
		return (1);
	else if (ft_strncmp(command_name, "export", len) == 0)
		return (1);
	else if (ft_strncmp(command_name, "unset", len) == 0)
		return (1);
	else
		return (0);
}
static int	auxiliar_backup(char *cmd, int std)

{
	int backup;

	if (cmd_env_change(cmd))
	{
		backup = open("back_up_temporal", O_WRONLY, O_CREAT, 0644);
		dup2(std, backup);
		return (backup);
	}
	return (0);
}
static void	close_pipes(int pipes[][2], size_t size, int actua_pipe)
{
	int	i;

	if (pipes)
		return ;
	i = 0;
	while (i <= actua_pipe - 1)
	{
		if (actua_pipe == i)
		{
			close(pipes[i][1]);
			if (actua_pipe != (int)size)
				close(pipes[i + 1][0]);
			return ;
		}
		else
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}
// Función para ejecutar todos los comandos con pipes
void execute_commands_with_pipes(t_gen_list *commands, t_gen_list *env)
{
    size_t n = commands->size;
    int (*pipes)[2] = malloc(sizeof(int[2]) * (n - 1));
    if (n > 1 && !pipes)
        return;

    // Crear pipes
    for (size_t i = 0; i < n - 1; i++)
        pipe(pipes[i]);

    t_iter it = iter_start(commands);
    t_command *cmd;
    pid_t *pids = malloc(sizeof(pid_t) * n);
    size_t i = 0;

    while ((cmd = iter_next(&it)) != NULL)
    {
        // Built-ins que modifican el entorno deben ejecutarse en el padre
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
            // Hijo: redirección de pipes
            if (i > 0) // leer del pipe anterior
            {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }
            if (i < n - 1) // escribir al pipe siguiente
            {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            // Cerrar todos los pipes en hijo
            for (size_t j = 0; j < n - 1; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // Ejecutar comando
            cmd->command_funct(cmd, env);
            exit(0);
        }
        else
        {
            // Padre guarda pid
            pids[i] = pid;
        }

        i++;
    }

    // Cerrar todos los pipes en padre
    for (size_t j = 0; j < n - 1; j++)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }

    // Esperar a todos los hijos
    for (size_t j = 0; j < i; j++)
        waitpid(pids[j], NULL, 0);

    free(pids);
    if (pipes)
        free(pipes);
}