/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:12:54 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/29 16:55:10 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bin_commandss_execution.h"
#include "../include/command.h"
#include "../include/envioroment.h"
#include "../list/list.h"
#include "../libft/libft.h"
#include <signal.h>

static char	**get_str_array_from_gen_list_args(t_gen_list *args)
{
	char	**result;
	t_node	*current_node;
	int		i;

	i = 0;
	result = ft_calloc(args->size + 1, sizeof(char *));
	current_node = args->head;
	while (current_node != NULL)
	{
		result[i] = ft_strdup((char *)current_node->value);
		current_node = current_node->next;
		i++;
	}
	return (result);
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

    env = get_str_array_from_envioroment_var_list(envioroment);
    cmd2 = get_str_array_from_gen_list_args(cmd->args);

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
	t_node				*current_node;
	t_envioroment_var	*current_node_value;

	if (!command)
		write(1, "a", 1);
	current_node = envioroment->head;
	while (current_node != NULL)
	{
		current_node_value = (t_envioroment_var *)current_node->value;
		ft_printf("%s=%s\n", current_node_value->var_name,
			current_node_value->var_value);
		current_node = current_node->next;
	}
}
void	export_execute(t_command *command, t_gen_list *envioroment)
{
	t_envioroment_var	*new_sport;
	t_node				*current_node;
	char				**new_variable;

	current_node = command->args->head->next;
	new_variable = ft_split2(current_node->value, '=');
	new_sport = init_envioroment_var(new_variable[0], new_variable[1]);
	free(new_variable);
	if (!contains_variable(envioroment, new_sport->var_name))
		push_end(envioroment, new_sport);
	else
	{
		add_var(envioroment, new_sport->var_value,
			new_sport->var_name);
		free(new_sport->var_name);
		free(new_sport);
	}
}
void	unset_execute(t_command *command, t_gen_list *envioroment)
{
	t_node	*current_node;

	current_node = command->args->head->next;
	remove_envioroment_var_from_name(envioroment, (char *)current_node->value);
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
