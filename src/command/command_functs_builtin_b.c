/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs_builtin_b.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 06:23:13 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 16:05:39 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"

int	pwd_execute(t_command *command, t_environment *environment)
{
	char			*current_dir;
	char			*arg;
	t_gen_list_iter	*it;

	it = gen_list_iter_start(command->args);
	gen_list_iter_next(it);
	arg = gen_list_iter_next(it);
	if (arg && arg[0] == '-')
	{
		gen_list_iter_destroy(it);
		return (COMMAND_ERR);
	}
	current_dir = env_get(environment, "PWD");
	gen_list_iter_destroy(it);
	if (!current_dir)
	{
		current_dir = getcwd(NULL, 0);
		if (!current_dir)
			return (COMMAND_ERR);
	}
	printf("%s\n", current_dir);
	free(current_dir);
	return (MS_OK);
}

int	env_execute(t_command *command, t_environment *environment)
{
	char	**serialized_env;
	size_t	i;

	if (!command || !environment)
		return (COMMAND_ERR);
	serialized_env = env_serialize_env(environment);
	i = 0;
	while (serialized_env[i] != NULL)
	{
		if (serialized_env[i][0] == '?')
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

static int	is_numeric_string(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '"' && str[i] != '\'')
			return (0);
		i++;
	}
	return (1);
}

static int	exit_code_without_quotes(char *arg)
{
	char	*temp;
	int		i;
	int		j;
	int		result;

	i = 0;
	j = 0;
	temp = ft_calloc(ft_strlen(arg), sizeof(char));
	while (arg[i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
			i++;
		else
		{
			temp[j] = arg[i];
			j++;
			i++;
		}
	}
	result = ft_atoi(temp);
	free(temp);
	return (result);
}

int	exit_execute(t_command *command, t_environment *environment)
{
	int		exit_code;
	char	*arg;

	exit_code = 0;
	(void)environment;
	if (gen_list_get_size(command->args) == 2)
	{
		free(gen_list_pop_front(command->args));
		arg = gen_list_pop_front(command->args);
		if (!is_numeric_string(arg))
			return (free(arg), COMMAND_NUMERIC_ARG_REQUIRED_ERR);
		exit_code = exit_code_without_quotes(arg);
		if(arg)
			free(arg);
	}
	else if (gen_list_get_size(command->args) > 2)
	{
		return (COMMAND_TOO_MANY_ARGS_ERR);
	}
	return (EXTERNALY_DEFINED_STATUS_CODE + ((exit_code + 256) % 256));
}
