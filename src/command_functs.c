/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:12:54 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/30 01:17:53 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bin_commandss_execution.h"
#include "../include/command.h"
#include "../include/environment.h"
#include "../list/list.h"
#include "../libft/libft.h"
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

    if (!cmd || !cmd->args || !cmd->args->head)
    {
        perror("No command args ");
        exit(1);
    }

    env = serialize_environment_vars(envioroment);
    cmd2 = serialize_to_string_array(cmd->args,serialize_arg);

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
    t_iter it;
    char *old_directory;
    char *target;
    char *joined_path;

    if (!command->args || command->args->size < 2)
    {
        fprintf(stderr, "cd: missing argument\n");
        return;
    }
    old_directory = get_var_value(environment, "PWD");
    it = iter_start(command->args);
    iter_next(&it);
    target = iter_next(&it);
    if (access(target, F_OK) == 0)
    {
        if (chdir(target) == -1)
        {
            perror("cd");
            free(old_directory);
            return;
        }
        if (old_directory)
            add_var(environment, old_directory, "OLDPWD");
        add_var(environment, ft_strdup(target), "PWD");
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
            add_var(environment, old_directory, "OLDPWD");
            add_var(environment, joined_path, "PWD");
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
	current_dir = get_var_value(envioroment, "PWD");
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
	serialized_env = serialize_environment_vars(envioroment);
	i = 0;
	while(i < envioroment->size)
	{
		printf("%s", serialized_env[i]);
		i++;
	}
	free_double_pointer(serialized_env);
}
void export_execute(t_command *command, t_gen_list *envioroment)
{
    t_node *current_node;
    char **new_variable;

    if (!command || !command->args || !envioroment)
        return;
    current_node = command->args->head->next;
    if (!current_node || !current_node->value)
        return;

    new_variable = ft_split2(current_node->value, '=');
    if (!new_variable || !new_variable[0] || !new_variable[1])
        return;

    add_var(envioroment, new_variable[0], new_variable[1]);
    size_t i = 0;
    while (i < 2)
    {
        free(new_variable[i]);
        i++;
    }
    free(new_variable);
}
void	unset_execute(t_command *command, t_gen_list *envioroment)
{
	t_node	*current_node;

	current_node = command->args->head->next;
	remove_var(envioroment, (char *)current_node->value);
}
void echo_execute(t_command *command, t_gen_list *envioroment)
{
    t_node *current_node;
    int newline = 1;
    size_t len;

    if (!command || !command->args || !command->args->head)
        return;

    current_node = command->args->head->next; // primer argumento real
    if (!current_node)
        return;

    // Comprobar -n usando ft_strncmp
    len = ft_strlen((char *)current_node->value);
    if (len == 2 && ft_strncmp((char *)current_node->value, "-n", 2) == 0)
    {
        newline = 0;
        current_node = current_node->next;
    }

    while (current_node)
    {
        ft_printf("%s", (char *)current_node->value);
        if (current_node->next)
            ft_printf(" ");
        current_node = current_node->next;
    }

    if (newline)
        ft_printf("\n");

    // No hacemos exit aquí; solo en hijos si se hace fork
	exit(0);
}
