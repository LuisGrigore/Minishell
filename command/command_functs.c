/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:12:54 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/01 14:02:32 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bin_commandss_execution.h"
#include "../include/command.h"
#include "../include/environment.h"
# include "../external/gen_list/gen_list.h"
#include "../external/libft/libft.h"
#include <signal.h>


static char *serialize_arg(void *arg_ptr)
{
	char *arg = (char *) arg_ptr;
	return (ft_strdup(arg));
}


void bin_execute(t_command *cmd, t_gen_list *envioroment)
{
    char **cmd2;
    char **env;
    char *path;

    if (!cmd || !cmd->args || gen_list_is_empty(cmd->args))
    {
        perror("No command args ");
        exit(1);
    }

    env = env_serialize(envioroment);
    cmd2 = gen_list_serialize_to_string_array(cmd->args,serialize_arg);

    path = find_command(env, cmd2[0]);
    if (!path)
    {
        perror("Path not found ");
        free_double_pointer(cmd2);
        exit(127);
    }

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

    execve(path, cmd2, env);

    perror("Failed to execute command ");
    free(path);
    free_double_pointer(cmd2);
    exit(1);
}
void cd_execute(t_command *command, t_gen_list *environment)
{
    t_gen_list_iter *it;
    char *old_directory;
    char *target;
    char *joined_path;

    if (!command->args || gen_list_get_size(command->args) < 2)
    {
        fprintf(stderr, "cd: missing argument\n");
        return;
    }
    old_directory = env_get(environment, "PWD");
    it = gen_list_iter_start(command->args);
    gen_list_iter_next(it);
    target = gen_list_iter_next(it);
    if (access(target, F_OK) == 0)
    {
        if (chdir(target) == -1)
        {
            perror("cd");
            free(old_directory);
            return;
        }
        if (old_directory)
            env_set(environment, old_directory, "OLDPWD");
        env_set(environment, ft_strdup(target), "PWD");
        free(old_directory);
        return;
    }
    if (old_directory)
    {
        joined_path = ft_strjoin(old_directory, target);
        if (access(joined_path, F_OK) == 0)
        {
            if (chdir(joined_path) == -1)
            {
                perror("cd");
                free(joined_path);
                free(old_directory);
                return;
            }
            env_set(environment, old_directory, "OLDPWD");
            env_set(environment, joined_path, "PWD");
            free(joined_path);
            free(old_directory);
            return;
        }
        free(joined_path);
    }
    fprintf(stderr, "cd: no such file or directory: %s\n", target);
    free(old_directory);
}

void	pwd_execute(t_command *command, t_gen_list *envioroment)
{
	char *current_dir;
	if (command == NULL)
		return ;
	current_dir = env_get(envioroment, "PWD");
	printf("%s\n", current_dir);
	free(current_dir);
	exit(0);
}
void	env_execute(t_command *command, t_gen_list *envioroment)
{
	char **serialized_env;
	int i;
	if (!command)
	{
		perror("env :");
		return;
	}
	serialized_env = env_serialize(envioroment);
	i = 0;
	while(i < gen_list_get_size(envioroment))
	{
		printf("%s", serialized_env[i]);
		i++;
	}
	free_double_pointer(serialized_env);
}
void export_execute(t_command *command, t_gen_list *envioroment)
{
    t_gen_list_iter *it;
    char **new_variable;
    char *arg;

    if (!command || !command->args || !envioroment)
        return;
    it = gen_list_iter_start(command->args);
    if (!it)
        return;
    arg = gen_list_iter_next(it);
    arg = gen_list_iter_next(it);
    gen_list_iter_destroy(it);
    if (!arg)
        return;
    new_variable = ft_split2(arg, '=');
    if (!new_variable || !new_variable[0] || !new_variable[1])
        return;
    env_set(envioroment, new_variable[0], new_variable[1]);
    for (size_t i = 0; i < 2; i++)
        free(new_variable[i]);
    free(new_variable);
}
void unset_execute(t_command *command, t_gen_list *envioroment)
{
    t_gen_list_iter *it;
    char *arg;

    if (!command || !command->args || !envioroment)
        return;
    it = gen_list_iter_start(command->args);
    if (!it)
        return;
    arg = gen_list_iter_next(it);
    arg = gen_list_iter_next(it);
    if (arg)
        env_unset(envioroment, arg);

    gen_list_iter_destroy(it);
}

void echo_execute(t_command *command, t_gen_list *envioroment)
{
    t_gen_list_iter *it;
    char *arg;
    int newline = 1;

    (void)envioroment;
    if (!command || !command->args)
        return;
    it = gen_list_iter_start(command->args);
    if (!it)
        return;
    arg = gen_list_iter_next(it);
    arg = gen_list_iter_next(it);
    if (arg && ft_strncmp(arg, "-n", 2) == 0 && ft_strlen(arg) == 2)
    {
        newline = 0;
        arg = gen_list_iter_next(it);
    }
    while (arg)
    {
        ft_printf("%s", arg);
        char *next_arg = gen_list_iter_next(it);
        if (next_arg)
            ft_printf(" ");
        arg = next_arg;
    }
    if (newline)
        ft_printf("\n");
    gen_list_iter_destroy(it);
    exit(0);
}

