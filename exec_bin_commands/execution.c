/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:41:33 by dmaestro          #+#    #+#             */
/*   Updated: 2025/05/03 19:41:35 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	execute(char **env, char *cmd, pid_t check);
static void	children(int *pipes, char **argv, char **env, int part, int ok);


void	exec_command(t_comand *cmd, char **env)
{
	int		pipes[2];
	pid_t	check;

	if (pipe(pipes) == -1)
		exit(1);

	check = fork();
	if (check == -1)
		exit(-1);
	if (check == 0)
		make_the_family(cmd ,pipes ,env, 2);
	parent(pipes, cmd, env, check);
}

 void	parent(int *pipes, t_comand *cmd, char **env, pid_t check)
{
	int	fd;

	fd = check_outfile(argv, pipes, check);
	dup2(fd, 1);
	dup2(pipes[0], 0);
	close(pipes[0]);
	close(pipes[1]);
	close(fd);
	execute(env, argv[ft_array_len(argv) - 2], check);
}

static void	children(int *pipes, t_comand *cmd, char **env, int part, int ok)
{
	int	fd;

	if (fd == -1)
	{
		close(pipes[0]);
		close(pipes[1]);
		error_manager(NULL, "Check the privilegies of the  input file", 0);
	}
	dup2(pipes[1], 1);
	close(pipes[0]);
	close(pipes[1]);
	execute(env, cmd->cmd, 0);
	exit(0);
}

static void	execute(char **env, char *cmd, pid_t check)
{
	char	**cmd2;
	char	*path;

	cmd2 = ft_split(cmd, ' ');
	if (!cmd2)
		error_manager(NULL, "Fail to split", check);
	path = find_command(env, cmd2[0], check);
	if (path == NULL)
		error_manager(cmd2, "the command isnt correct", check);
	execve(path, cmd2, env);
	if(path)
		free(path);
	free_double_pointer(cmd2);
}

void make_the_family(t_comand *cmd, int *pipes , char **env, int ok)
{
	pid_t check[size_of_list(cmd) - 1];
    t_comand *aux;
	int i;

	i = 0;
    aux = cmd;
	while (cmd->next != NULL)
	{
		check[i] = fork();
		if(check[i] == 0)
			children(pipes, aux->cmd ,env, i + ok, ok);
		i++;
        aux = aux->next;
	}
	i = 0;
	while(check[i  -1])
	{
		waitpid(check[i], NULL, 0);
		i++;
	}

}
