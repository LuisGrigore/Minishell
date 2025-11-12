/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs_bin_a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:20:05 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/12 08:32:22 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"
#include "include/ms_status_codes.h"
#include <errno.h>

static char	*serialize_arg(void *arg_ptr)
{
	char	*arg;

	arg = (char *)arg_ptr;
	return (ft_strdup(arg));
}

static int	check_error(int find_err)
{
	if (find_err == EACCES)
		return (COMMAND_PERMISSION_ERR);
	if (find_err == EISDIR)
		return (COMMAND_IS_DIR_ERR);
	if (find_err == ENOENT)
		return (COMMAND_NO_SUCH_FILE_OR_DIR_ERR);
	return (COMMAND_NOT_FOUND_ERR);
}

int	bin_execute(t_command *cmd, t_environment *environment)
{
	char	**cmd2;
	char	**env;
	char	*path;
	int		find_err;

	if (!cmd || !cmd->args || gen_list_is_empty(cmd->args))
		return (COMMAND_MALFORMED_ERR);
	env = env_serialize(environment);
	cmd2 = gen_list_serialize_to_string_array(cmd->args, serialize_arg);
	find_err = 0;
	path = find_command(env, cmd2[0], &find_err);
	if (!path)
	{
		free_double_pointer(env);
		free_double_pointer(cmd2);
		return (check_error(find_err));
	}
	signals_restore();
	execve(path, cmd2, env);
	return (COMMAND_ERR);
}
