/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:12:54 by dmaestro          #+#    #+#             */
/*   Updated: 2025/05/13 19:12:55 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/command_functs.h"
#include "../include/bin_commandss_execution.h"
#include "../include/envioroment.h"
#include "../libft/libft.h"

void	bin_execute(t_command *cmd ,t_gen_list *envioroment)
{
	char	**cmd2;
    char    **env;
	char	*path;

    env = get_str_array_from_envioroment_var_list(envioroment);
    cmd2 = get_str_array_from_gen_list_args(cmd->args);
	if (!cmd->args)
	{ 	
		write(2, "Fail to split\n", 15);
		exit(1);
	}
	path = find_command(env, envioroment->head->value);
	if (path == NULL)
	{ 	
		write(2, "Path doesnt found\n", 15);
		exit(1);
	}
	execve(path, cmd2, env);
	if(path)
		free(path);
	free_double_pointer(cmd2);
}
void    cd_execute(t_command *command,t_gen_list *envioroment)
{
    char *new_directory;
    char *old_directory;
    t_node  *current_node;

    old_directory = ft_strdup(get_var_value_from_name(envioroment, "PWD"));
    current_node = command->args->head->next;
    if(access(current_node->value, F_OK) == 0)
    {
        if(chdir(current_node->value) == -1)
            perror("This file :Not a directory");
        else
        { 
            change_env_value(envioroment, ft_strdup(current_node->value), "PWD");
            
            return ;
        }
    }
    new_directory = ft_strjoin(old_directory, current_node->value);
    if(access(new_directory, F_OK) == 0)
    {
        if(chdir(new_directory) == -1)
            perror("This file :Not a directory");
        else
        { 
            change_env_value(envioroment, ft_strdup(current_node->value), "PWD");
            change_env_value(envioroment, old_directory, "OLD_PWD");
            return ;
        }
    }
}

void pwd_execute(t_command *command, t_gen_list *envioroment)
{
    printf("%s\n", get_var_value_from_name(envioroment, "PWD"));
}
void env_execute(t_command *command, t_gen_list *envioroment)
{
    t_node *current_node;
    t_envioroment_var *current_node_value;

    current_node = envioroment->head;
    while(current_node != NULL)
    {
        current_node_value = (t_envioroment_var *)current_node->value;
        ft_printf("%s=%s\n",current_node_value->var_name, current_node_value->var_value);
        current_node = current_node->next;
    }
}
