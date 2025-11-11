#include "command_internal.h"
#include <stdio.h>

static int	check_option_of_export(char **new_variable, t_environment *env)
{
	char	*temp;
	int		i;
	char	*temp2;

	i = 0;
	while (new_variable[0][i])
	{
		if (!ft_isalnum(new_variable[0][i]))
		{
			if (new_variable[0][i] != '+'
				|| i != (int)ft_strlen(new_variable[0]) - 1)
				return (-1);
			else
				break ;
		}
		i++;
		if (!new_variable[0][i])
			return (0);
	}
	temp = ft_substr(new_variable[0], 0, ft_strlen(new_variable[0]) - 1);
	free(new_variable[0]);
	new_variable[0] = temp;
	temp = env_get(env, new_variable[0]);
	if (!temp)
		return (0);
	temp2 = new_variable[1];
	new_variable[1] = ft_strjoin(temp, temp2);
	return (free(temp), free(temp2), 0);
}
static int	export_loop(char *arg, t_environment *environment,
		t_gen_list_iter *it)
{
	char	**new_variable;

	while (arg)
	{
		if (ft_isdigit(arg[0]))
			return (COMMAND_MALFORMED_ERR);
		if (ft_strlen(arg) == 1 && arg[0] == '=')
			return (COMMAND_MALFORMED_ERR);
		new_variable = simple_split(arg, '=');
		if (!new_variable || !new_variable[0])
			return (MS_ALLOCATION_ERR);
		if (check_option_of_export(new_variable, environment) == -1)
		{
			if (new_variable[1])
				free(new_variable[1]);
			free(new_variable[0]);
			return (free(new_variable), COMMAND_MALFORMED_ERR);
		}
		if (ft_strchr(arg, '='))
			env_set(environment, new_variable[0], new_variable[1]);
		free(new_variable[0]);
		if (new_variable[1])
			free(new_variable[1]);
		free(new_variable);
		arg = gen_list_iter_next(it);
	}
	return (MS_OK);
}
int	export_execute(t_command *command, t_environment *environment)
{
	t_gen_list_iter	*it;
	char			*arg;
	int				status_code;

	// char			**new_variable;
	if (!command || !environment)
		return (COMMAND_ERR);
	if (!command->args)
		return (COMMAND_MALFORMED_ERR);
	it = gen_list_iter_start(command->args);
	if (!it)
		return (MS_ALLOCATION_ERR);
	arg = gen_list_iter_next(it);
	arg = gen_list_iter_next(it);
	status_code = export_loop(arg, environment, it);
	gen_list_iter_destroy(it);
	return (status_code);
}

int	unset_execute(t_command *command, t_environment *environment)
{
	t_gen_list_iter	*it;
	char			*arg;

	if (!command || !environment)
		return (COMMAND_ERR);
	if (!command->args)
		return (COMMAND_MALFORMED_ERR);
	it = gen_list_iter_start(command->args);
	if (!it)
		return (MS_ALLOCATION_ERR);
	arg = gen_list_iter_next(it);
	arg = gen_list_iter_next(it);
	while (arg)
	{
		env_unset(environment, arg);
		arg = gen_list_iter_next(it);
	}
	gen_list_iter_destroy(it);
	return (MS_OK);
}
static void	echo_loop(char *arg, t_gen_list_iter *it)
{
	char	*next_arg;

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
	if (arg && ft_strncmp(arg, "-n", 2) == 0 && ft_strlen(arg) == 2)
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
