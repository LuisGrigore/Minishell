#include "command_internal.h"
#include <stdio.h>

int	export_execute(t_command *command, t_gen_list *environment)
{
	t_gen_list_iter	*it;
	char			*arg;
	char			**new_variable;

	if (!command || !environment)
		return (COMMAND_ERR);
	if (!command->args)
		return (COMMAND_MALFORMED_ERR);
	if (gen_list_get_size(command->args) < 2)
		return (COMMAND_MISSING_ARGS_ERR);
	if (gen_list_get_size(command->args) > 2)
		return (COMMAND_TOO_MANY_ARGS_ERR);
	it = gen_list_iter_start(command->args);
	if (!it)
		return (MS_ALLOCATION_ERR);
	arg = gen_list_iter_next(it);
	arg = gen_list_iter_next(it);
	gen_list_iter_destroy(it);
	new_variable = ft_split2(arg, '=');
	if (!new_variable || !new_variable[0] || !new_variable[1])
		return (MS_ALLOCATION_ERR);
	if (check_option_of_export(new_variable, environment) == -1)
		return (COMMAND_INVALID_ARGS_ERR);
	env_set(environment, new_variable[0], new_variable[1]);
	free(new_variable[0]);
	free(new_variable[1]);
	free(new_variable);
	return (MS_OK);
}

int	unset_execute(t_command *command, t_gen_list *environment)
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

int	echo_execute(t_command *command, t_gen_list *environment)
{
	t_gen_list_iter	*it;
	char			*arg;
	int				newline;
	char			*next_arg;

	(void)environment;
	if (!command )
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
	while (arg)
	{
		ft_printf("%s", arg);
		next_arg = gen_list_iter_next(it);
		if (next_arg)
			ft_printf(" ");
		arg = next_arg;
	}
	if (newline)
		ft_printf("\n");
	gen_list_iter_destroy(it);
	return (MS_OK);
}
