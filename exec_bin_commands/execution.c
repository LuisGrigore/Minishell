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

static void	execute(char **env, t_command *cmd);
static void	parent(int *pipes, t_command *cmd, char **env, pid_t *check);

 static void	parent(int *pipes, t_command *cmd, char **env, pid_t *check)
{
	check[1] = fork();
	dup2(pipes[0], 0);
	close(pipes[0]);
	close(pipes[1]);
	if(check[1] == 0)
		execute(env, cmd);
	waitpid(check[0], NULL, 0);
	waitpid(check[1], NULL, 0);
	exit(0);

}

void	children(int *pipes, t_command *cmd, char **env)
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


