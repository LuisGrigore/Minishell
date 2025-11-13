/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs_builtin_c.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 06:12:33 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 20:48:50 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"

static void	echo_loop(char *arg, t_gen_list_iter *it)
{
	char	*next_arg;

	while (arg)
	{
		if (ft_strncmp("-n", arg, 2) == 0)
		{
			next_arg = gen_list_iter_next(it);
			arg = next_arg;
		}
		else
			break ;
	}
	while (arg)
	{
		ft_printf("%s", arg);
		next_arg = gen_list_iter_next(it);
		if (next_arg)
			ft_printf(" ");
		arg = next_arg;
	}
}

int	echo_execute(t_command *command, t_environment *environment)
{
	t_gen_list_iter	*it;
	char			*arg;
	int				newline;

	(void)environment;
	if (!command)
		return (COMMAND_ERR);
	if (!command->args)
		return (COMMAND_MALFORMED_ERR);
	it = gen_list_iter_start(command->args);
	if (!it)
		return (MS_ALLOCATION_ERR);
	arg = gen_list_iter_next(it);
	arg = gen_list_iter_next(it);
	newline = 1;
	if (arg && ft_strncmp(arg, "-n", 2) == 0)
	{
		newline = 0;
		arg = gen_list_iter_next(it);
	}
	echo_loop(arg, it);
	if (newline)
		ft_printf("\n");
	gen_list_iter_destroy(it);
	return (MS_OK);
}

static int	cd_args_checker(t_command *command, t_environment *environment,
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

int	cd_execute(t_command *command, t_environment *environment)
{
	t_gen_list_iter	*it;
	char			*old_directory;
	char			*target;
	int				checker_status;

	checker_status = cd_args_checker(command, environment, &it);
	if (checker_status != MS_OK)
		return (checker_status);
	old_directory = getcwd(NULL, 0);
	if (gen_list_get_size(command->args) < 2)
		return (gen_list_iter_destroy(it), cd_no_args(old_directory,
				environment));
	gen_list_iter_next(it);
	target = gen_list_iter_next(it);
	gen_list_iter_destroy(it);
	if (access(target, F_OK) == 0)
	{
		if (chdir(target) == -1)
			return (free(old_directory), MS_PATH_ERR);
		env_set(environment, "OLDPWD", old_directory);
		target = getcwd(NULL, 0);
		env_set(environment, "PWD", target);
		return (free(target), free(old_directory), MS_OK);
	}
	return (MS_PATH_ERR);
}
