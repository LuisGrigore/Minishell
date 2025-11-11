/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs_bin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/11/11 17:33:19 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"
#include "include/ms_status_codes.h"
#include <errno.h>
#include <sys/stat.h>

static char	*get_final_path(char *path, char *cmd)
{
	char	*aux;
	char	*result;

	aux = ft_strjoin(path, "/");
	result = ft_strjoin(aux, cmd);
	free(aux);
	return (result);
}

/*
 * find_command: search for 'cmd' in PATH (env array) or treat it as given path.
 * If found and executable returns an allocated string with the full path.
 * If not found returns NULL and sets *err_out to 0.
 * If found but not executable sets *err_out to EACCES (permission) or EISDIR (is dir).
 */
static char *find_command(char **env, char *cmd, int *err_out)
{
	int y = 0;
	char **path = NULL;
	char *final_path;
	int seen_permission_error = 0;
	struct stat st;

	if (err_out)
		*err_out = 0;

	/* If cmd contains a slash treat it as a path */
	if (ft_strchr(cmd, '/'))
	{
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

	/* find PATH= in env */
	while (env && env[y] && ft_strncmp(env[y], "PATH=", 5) != 0)
		y++;
	if (!env || !env[y])
	{
		/* No PATH: try cmd in current working directory / as provided */
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		{
			if (err_out)
				*err_out = EISDIR;
			return (NULL);
		}
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			if (err_out)
				*err_out = EACCES;
			return (NULL);
		}
		return (NULL);
	}

	path = ft_split(env[y] + 5, ':');
	y = 0;
	while (path && path[y])
	{
		final_path = get_final_path(path[y], cmd);
		if (stat(final_path, &st) == 0 && S_ISDIR(st.st_mode))
		{
			free(final_path);
			y++;
			continue;
		}
		if (access(final_path, F_OK) == 0)
		{
			if (access(final_path, X_OK) == 0)
			{
				free_double_pointer(path);
				return (final_path);
			}
			else
				seen_permission_error = 1;
		}
		free(final_path);
		y++;
	}
	free_double_pointer(path);
	if (seen_permission_error)
	{
		if (err_out)
			*err_out = EACCES;
	}
	return (NULL);
}

static char	*serialize_arg(void *arg_ptr)
{
	char	*arg;

	arg = (char *)arg_ptr;
	return (ft_strdup(arg));
}

int	bin_execute(t_command *cmd, t_environment *environment)
{
	char	**cmd2;
	char	**env;
	char	*path;

	if (!cmd || !cmd->args || gen_list_is_empty(cmd->args))
	{
		return (COMMAND_MALFORMED_ERR);
	}
	env = env_serialize(environment);
	cmd2 = gen_list_serialize_to_string_array(cmd->args, serialize_arg);
	int find_err = 0;
	path = find_command(env, cmd2[0], &find_err);
	if (!path)
	{
		free_double_pointer(env);
		free_double_pointer(cmd2);
		if (find_err == EACCES)
			return (COMMAND_PERMISSION_ERR);
		if (find_err == EISDIR)
			return (COMMAND_IS_DIR_ERR);
		if (find_err == ENOENT)
			return (COMMAND_NO_SUCH_FILE_OR_DIR_ERR);
		return (COMMAND_NOT_FOUND_ERR);
	}
	signals_restore();
	execve(path, cmd2, env);
	return (COMMAND_ERR);
}
