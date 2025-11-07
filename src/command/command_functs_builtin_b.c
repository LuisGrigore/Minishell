#include "command_internal.h"

// TODO: manejar el cd sin argumentos (home) y manejar bien las rutas relativas y absolutas
int	cd_execute(t_command *command, t_gen_list *environment)
{
	t_gen_list_iter	*it;
	char			*old_directory;
	char			*target;
	if (gen_list_get_size(command->args) > 2)
	{
		fprintf(stderr, "cd: too many arguments\n");
		return (BINBUILTIN_ERROR);
	}
	if (!command || !command->args || gen_list_get_size(command->args) < 2)
	{
		fprintf(stderr, "cd: missing argument\n");
		return (-1);
	}
	old_directory = getenv("PWD");
	it = gen_list_iter_start(command->args);
	gen_list_iter_next(it);
	target = gen_list_iter_next(it);
	if (access(target, F_OK) == 0)
	{
		if (chdir(target) == -1)
		{
			ft_printf("bash: cd:");
			free(old_directory);
			return (BINBUILTIN_ERROR);
		}
		if (old_directory)
			env_set(environment, "OLDPWD", old_directory);
		env_set(environment, "PWD", ft_strdup(getcwd(NULL, 0)));
		return (0);
	}
	fprintf(stderr, "bash: cd: %s: No such file or directory\n", target);
	return (BINBUILTIN_ERROR);
}

int	pwd_execute(t_command *command, t_gen_list *environment)
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
		printf("bash: pwd: %s option not supported\n", arg);
		return (BINBUILTIN_ERROR);
	}
	current_dir = env_get(environment, "PWD");
	if (!current_dir)
	{
		current_dir = getcwd(NULL, 0);
		if (!current_dir)
		{
			perror("pwd");
			return (ENVIRONMENT_ERR);
		}
	}
	printf("%s\n", current_dir);
	gen_list_iter_destroy(it);
	free(current_dir);
	return (BINBUILTIN_SUCCESS);
}
int	env_execute(t_command *command, t_gen_list *environment)
{
	char	**serialized_env;
	size_t	i;

	if (!command)
	{
		perror("env :");
		return (COMMAND_ERROR);
	}
	serialized_env = env_serialize(environment);
	i = 0;
	while (i < gen_list_get_size(environment))
	{
		printf("%s\n", serialized_env[i]);
		i++;
	}
	free_double_pointer(serialized_env);
	return (BINBUILTIN_SUCCESS);
}

int	exit_execute(t_command *command, t_gen_list *environment)
{
	int exit_code;

	exit_code = 0;
	(void) environment;
	if (gen_list_get_size (command->args) == 2)
	{
		gen_list_pop_front(command->args);
		exit_code = ft_atoi((char *)gen_list_pop_front(command->args));
	}
	else if (gen_list_get_size (command->args) > 2)
	{
		return (BUILTIN_TOO_MANY_ARGS);
	}
	return (EXIT_USER_DEFINED_STATUS_CODE + exit_code);
}