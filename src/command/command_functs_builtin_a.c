/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs_builtin_a.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 06:40:29 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 20:41:19 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"
#include <stdio.h>

static int	export_loop(char *arg, t_environment *environment,
		t_gen_list_iter *it)
{
	char	**new_variable;

	if (!arg)
		return (MS_OK);
	if (checker_export_loop(arg) != MS_OK)
		return (COMMAND_MALFORMED_ERR);
	new_variable = simple_split(arg, '=');
	if (!new_variable || !new_variable[0])
		return (MS_ALLOCATION_ERR);
	if (check_option_of_export(new_variable, environment) == -1)
		return (double_pontier_free(new_variable), COMMAND_MALFORMED_ERR);
	if (ft_strchr(arg, '=') && ft_strncmp(new_variable[0], "0", 1) == 0)
		env_set(environment, new_variable[0], "");
	else if (!ft_strchr(arg, '='))
		env_set(environment, new_variable[0], NULL);
	else
		env_set(environment, new_variable[0], new_variable[1]);
	free(new_variable[0]);
	if (new_variable[1])
		free(new_variable[1]);
	return (free(new_variable), export_loop(gen_list_iter_next(it), environment,
			it));
}

static int	print_export(t_command *command, t_environment *environment)
{
	char	**serialized_env;
	size_t	i;

	if (!command || !environment)
		return (COMMAND_ERR);
	serialized_env = env_serialize_export(environment);
	sort_export(serialized_env);
	i = 0;
	while (serialized_env[i] != NULL)
	{
		if (ft_strncmp("declare -x ?", serialized_env[i],
				ft_strlen("declare -x ?")) == 0)
		{
			i++;
			continue ;
		}
		printf("%s\n", serialized_env[i]);
		i++;
	}
	free_double_pointer(serialized_env);
	return (MS_OK);
}

int	export_execute(t_command *command, t_environment *environment)
{
	t_gen_list_iter	*it;
	char			*arg;
	int				status_code;

	if (!command || !environment)
		return (COMMAND_ERR);
	if (!command->args)
		return (COMMAND_MALFORMED_ERR);
	if (gen_list_get_size(command->args) < 2)
		return (print_export(command, environment));
	it = gen_list_iter_start(command->args);
	if (!it)
		return (MS_ALLOCATION_ERR);
	arg = gen_list_iter_next(it);
	arg = gen_list_iter_next(it);
	status_code = export_loop(arg, environment, it);
	gen_list_iter_destroy(it);
	return (status_code);
}
