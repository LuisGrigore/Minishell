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

#include "../include/bin_commandss_execution.h"

static void make_the_family(t_command *cmd, int *pipes , char **env);
static void	execute(char **env, t_command *cmd);
static void	children(int *pipes, t_command *cmd, char **env);
static void	parent(int *pipes, t_command *cmd, char **env);


void	exec_command(t_command *cmd, t_envioroment *envioroment)
{
	int		pipes[2];
	char	**env;
	pid_t	check[2];

	check[0] = 0;
	env = env_to_dbarray(envioroment);
	if (pipe(pipes) == -1)
		exit(1);
	if(size_of_list(cmd) >= 2)
	{ 	
		check[0] = fork();
		if (check[0] == 0)
			make_the_family(cmd ,pipes ,env);
	}
	check[1] = fork();
	if(check[1] == 0)
		parent(pipes,lst_commad(cmd), env);
	waitpid(check[0], NULL, 0);
	waitpid(check[1], NULL, 0);
	exit(0);
}

 static void	parent(int *pipes, t_command *cmd, char **env)
{

	dup2(pipes[0], 0);
	close(pipes[0]);
	close(pipes[1]);
	execute(env, cmd);

}

static void	children(int *pipes, t_command *cmd, char **env)
{
	dup2(pipes[1], 1);
	close(pipes[0]);
	close(pipes[1]);
	execute(env, cmd);
	exit(0);
}

static void	execute(char **env, t_command *cmd)
{
	char	**cmd2;
	char	*path;

	cmd2 = ft_split2(cmd->cmd, ' ');
	if (!cmd2)
	{ 	
		write(2, "Fail to split\n", 15);
		exit(1);
	}
	path = find_command(env, cmd2[0]);
	if (path == NULL)
	{ 	
		write(2, "Path doesnt found\n", 15);
		exit(1);
	}
	execve(path, cmd2, env);
	if(path)
		free(path);
	free_double_pointer(cmd2);
}

void make_the_family(t_command *cmd, int *pipes , char **env)
{
	pid_t check[size_of_list(cmd) - 1];
    t_command *aux;
	int i;

	i = 0;
    aux = cmd;
	while (cmd->next != NULL)
	{
		check[i] = fork();
		if(check[i] == 0)
			children(pipes, aux ,env);
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
