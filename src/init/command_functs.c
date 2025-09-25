/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:12:54 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/23 18:00:23 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bin_commandss_execution.h"
#include "../include/command_functs.h"
#include "../libft/libft.h"

void	bin_execute(t_command *cmd, t_gen_list *envioroment)
{
	char	**cmd2;
	char	**env;
	char	*path;

	env = get_str_array_from_envioroment_var_list(envioroment);
	cmd2 = get_str_array_from_gen_list_args(cmd->args);
	write(1, "hola", 4);
	if (!cmd->args)
	{
		write(2, "Fail to split\n", 15);
		exit(1);
	}
	path = find_command(env, cmd2[0]);
	if (path == NULL)
	{
		write(2, "Path doesnt found\n", 19);
		exit(1);
	}
	execve(path, cmd2, env);
	if (path)
		free(path);
	free_double_pointer(cmd2);
}
void	cd_execute(t_command *command, t_gen_list *envioroment)
{
	char	*new_directory;
	char	*old_directory;
	t_node	*current_node;

	old_directory = ft_strdup(get_var_value_from_name(envioroment, "PWD"));
	current_node = command->args->head->next;
	if (access(current_node->value, F_OK) == 0)
	{
		if (chdir(current_node->value) == -1)
			perror("This file :Not a directory");
		else
		{
			change_env_value(envioroment, ft_strdup(current_node->value),
				"PWD");
			return ;
		}
	}
	new_directory = ft_strjoin(old_directory, current_node->value);
	if (access(new_directory, F_OK) == 0)
	{
		if (chdir(new_directory) == -1)
			perror("This file :Not a directory");
		else
		{
			change_env_value(envioroment, ft_strdup(current_node->value),
				"PWD");
			change_env_value(envioroment, old_directory, "OLD_PWD");
			return ;
		}
	}
}

void	pwd_execute(t_command *command, t_gen_list *envioroment)
{
	if (command == NULL)
		return ;
	printf("%s\n", get_var_value_from_name(envioroment, "PWD"));
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
	new_sport = init_envioroment_var();
	new_sport->var_name = new_variable[0];
	new_sport->var_value = new_variable[1];
	free(new_variable);
	if (get_var_value_from_name(envioroment, new_sport->var_name) == NULL)
		insert_end(envioroment, new_sport);
	else
	{
		change_env_value(envioroment, new_sport->var_value,
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
void	echo_execute(t_command *command, t_gen_list *envioroment)
{
	t_node	*current_node;
	size_t	len;

	len = command->args->size--;
	if (!envioroment)
		return ;
	current_node = command->args->head->next;
	if (ft_strncmp((char *)current_node->value, "-n", 2) == 0)
		current_node = current_node->next;
	while (current_node != NULL && len != 1)
	{
		ft_printf("%s ", current_node->value);
		current_node = current_node->next;
		len--;
	}
	if (current_node)
		ft_printf("%s\n", current_node->value);
	exit(0);
}
