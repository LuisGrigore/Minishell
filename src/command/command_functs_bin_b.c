/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs_bin_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:16:32 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/12 08:19:38 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"
#include <errno.h>
#include <sys/stat.h>

static char	*abslote_route_command(char *cmd, int *err_out)
{
	struct stat	st;

	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		if (err_out)
			*err_out = EISDIR;
		return (NULL);
	}
	if (access(cmd, F_OK) != 0)
	{
		if (err_out)
			*err_out = errno;
		return (NULL);
	}
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (err_out)
		*err_out = EACCES;
	return (NULL);
}

static char	*command_path_find(char **path, char *cmd,
		int *seen_permission_error)
{
	char		*final_path;
	struct stat	st;
	int			y;

	y = 0;
	while (path && path[y])
	{
		final_path = get_final_path(path[y], cmd);
		if (stat(final_path, &st) == 0 && S_ISDIR(st.st_mode))
		{
			free(final_path);
			y++;
			continue ;
		}
		if (access(final_path, F_OK) == 0)
		{
			if (access(final_path, X_OK) == 0)
				return (final_path);
			else
				*seen_permission_error = 1;
		}
		free(final_path);
		y++;
	}
	return (NULL);
}

char	*find_command(char **env, char *cmd, int *err_out)
{
	int		y;
	char	**path;
	char	*final_path;
	int		seen_permission_error;

	y = 0;
	path = NULL;
	seen_permission_error = 0;
	if (err_out)
		*err_out = 0;
	if (ft_strchr(cmd, '/'))
		return (abslote_route_command(cmd, err_out));
	while (env && env[y] && ft_strncmp(env[y], "PATH=", 5) != 0)
		y++;
	if (!env || !env[y])
		return (abslote_route_command(cmd, err_out));
	path = ft_split(env[y] + 5, ':');
	final_path = command_path_find(path, cmd, &seen_permission_error);
	if (seen_permission_error)
	{
		if (err_out)
			*err_out = EACCES;
	}
	return (free_double_pointer(path), final_path);
}
