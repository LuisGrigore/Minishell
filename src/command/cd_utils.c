/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:35:45 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 20:36:03 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"

int	cd_args_checker(t_command *command, t_environment *environment,
		t_gen_list_iter **it)
{
	if (!command || !environment)
		return (COMMAND_ERR);
	if (!command->args)
		return (COMMAND_MALFORMED_ERR);
	if (gen_list_get_size(command->args) > 2)
		return (COMMAND_TOO_MANY_ARGS_ERR);
	*it = gen_list_iter_start(command->args);
	if (*it == NULL)
		return (MS_ALLOCATION_ERR);
	return (MS_OK);
}

int	cd_no_args(char *old_pwd, t_environment *environment)
{
	char	*home;
	char	*aux;

	aux = env_get(environment, "USER");
	chdir("/");
	home = ft_strjoin("home/", aux);
	free(aux);
	if (home)
	{
		if (chdir(home) == -1)
			return (free(home), free(old_pwd), MS_PATH_ERR);
		env_set(environment, "OLDPWD", old_pwd);
		aux = getcwd(NULL, 0);
		env_set(environment, "PWD", aux);
		return (free(home), free(old_pwd), free(aux), MS_OK);
	}
	return (free(old_pwd), MS_PATH_ERR);
}
