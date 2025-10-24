/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs_bin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:12:54 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/24 06:56:00 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"

static char	*get_final_path(char *path, char *cmd)
{
	char	*aux;
	char	*result;

	aux = ft_strjoin(path, "/");
	result = ft_strjoin(aux, cmd);
	free(aux);
	return (result);
}

static char	*checker_path(char *env, char *cmd)
{
	if (!env && access(cmd, X_OK) != 0)
	{
		write(2, "Path doest find\n", 17);
		exit(1);
	}
	else if (access(cmd, X_OK) == 0)
		return (cmd);
	return (NULL);
}

static char	*find_command(char **env, char *cmd)
{
	int		y;
	char	**path;
	char	*final_path;

	y = 0;
	while (env[y] && ft_strncmp(env[y], "PATH=", 5) != 0)
		y++;
	if (checker_path(env[y], cmd))
		return (checker_path(env[y], cmd));
	path = ft_split(env[y] + 5, ':');
	y = 0;
	while (path[y])
	{
		final_path = get_final_path(path[y], cmd);
		if (access(final_path, X_OK) == 0)
		{
			free_double_pointer(path);
			return (final_path);
		}
		free(final_path);
		y++;
	}
	free_double_pointer(path);
	return (NULL);
}

static char *serialize_arg(void *arg_ptr)
{
	char *arg = (char *) arg_ptr;
	return (ft_strdup(arg));
}


void bin_execute(t_command *cmd, t_gen_list *envioroment)
{
    char **cmd2;
    char **env;
    char *path;
	
	
    if (!cmd || !cmd->args || gen_list_is_empty(cmd->args))
    {
        perror("No command args ");
        exit(1);
    }

    env = env_serialize(envioroment);
    cmd2 = gen_list_serialize_to_string_array(cmd->args,serialize_arg);

    path = find_command(env, cmd2[0]);
    if (!path)
    {
        perror("Path not found ");
        free_double_pointer(cmd2);
        exit(127);
    }

    signals_restore();

    execve(path, cmd2, env);

    perror("Failed to execute command ");
    free(path);
    free_double_pointer(cmd2);
    exit(1);
}



