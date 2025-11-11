#include "command_internal.h"

static int	cd_args_checker(t_command *command, t_environment *environment,
		t_gen_list_iter **it)
{
	if (!command || !environment)
		return (COMMAND_ERR);
	if (!command->args)
		return (COMMAND_MALFORMED_ERR);
	if (gen_list_get_size(command->args) > 2)
		return (COMMAND_TOO_MANY_ARGS_ERR);
	if (gen_list_get_size(command->args) < 2)
		return (COMMAND_MISSING_ARGS_ERR);
	*it = gen_list_iter_start(command->args);
	if (*it == NULL)
		return (MS_ALLOCATION_ERR);
	return (MS_OK);
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
	old_directory = getenv("PWD");
	gen_list_iter_next(it);
	target = gen_list_iter_next(it);
	gen_list_iter_destroy(it);
	if (access(target, F_OK) == 0)
	{
		if (chdir(target) == -1)
			return (free(old_directory), MS_PATH_ERR);
		if (old_directory)
			env_set(environment, "OLDPWD", old_directory);
		target = getcwd(NULL, 0);
		env_set(environment, "PWD", target);
		return (free(target), MS_OK);
	}
	return (MS_PATH_ERR);
}

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
	if (!current_dir)
	{
		current_dir = getcwd(NULL, 0);
		if (!current_dir)
			return (COMMAND_ERR);
	}
	printf("%s\n", current_dir);
	gen_list_iter_destroy(it);
	free(current_dir);
	return (MS_OK);
}
int	env_execute(t_command *command, t_environment *environment)
{
	char	**serialized_env;
	size_t	i;

	if (!command || !environment)
		return (COMMAND_ERR);
	serialized_env = env_serialize(environment);
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
		gen_list_pop_front(command->args);
		arg = gen_list_pop_front(command->args);
		if (!is_numeric_string(arg))
			return (COMMAND_NUMERIC_ARG_REQUIRED_ERR);
		exit_code = exit_code_without_quotes(arg);
	}
	else if (gen_list_get_size(command->args) > 2)
	{
		return (COMMAND_TOO_MANY_ARGS_ERR);
	}
	return (EXTERNALY_DEFINED_STATUS_CODE + ((exit_code + 256) % 256));
}
