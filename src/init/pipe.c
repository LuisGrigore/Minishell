/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:15:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/23 19:32:01 by dmaestro         ###   ########.fr       */
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
			printf("es esto?");
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
