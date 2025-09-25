/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:33:23 by dmaestro          #+#    #+#             */
/*   Updated: 2025/05/10 18:56:49 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bin_commandss_execution.h"
#include "../libft/libft.h"
#include "unistd.h"

static char	*checker_path(char *env, char *cmd);
static char	*get_final_path(char *path, char *cmd)
{
	char	*aux;
	char	*result;

	aux = ft_strjoin(path, "/");
	result = ft_strjoin(aux, cmd);
	free(aux);
	return (result);
}

char	*find_command(char **env, char *cmd)
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