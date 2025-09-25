/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envioroment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:35:48 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/23 19:15:36 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command_functs.h"
#include "../include/envioroment.h"
#include "../libft/libft.h"
#include "stdlib.h"
#include <stdio.h>

t_envioroment_var	*init_envioroment_var(void)
{
	t_envioroment_var	*new_env;

	new_env = ft_calloc(1, sizeof(t_envioroment_var));
	new_env->var_name = NULL;
	new_env->var_value = NULL;
	return (new_env);
}

t_envioroment_var	*init_envioroment_var_name_value(char *name, char *value)
{
	t_envioroment_var	*new_env;

	new_env = init_envioroment_var();
	new_env->var_name = name;
	new_env->var_value = value;
	return (new_env);
}

t_gen_list	*get_environment_var_list_from_str_array(char **str_array)
{
	int			i;
	t_gen_list	*env_var_list;
	char		**var_str_name_value_split;

	i = 0;
	env_var_list = init_list();
	while (str_array[i])
	{
		var_str_name_value_split = ft_split(str_array[i], '=');
		insert_end(env_var_list,
			init_envioroment_var_name_value(var_str_name_value_split[0],
				var_str_name_value_split[1]));
		free(var_str_name_value_split);
		i++;
	}
	return (env_var_list);
}

char	*get_var_value_from_name(t_gen_list *environment_vars, char *name)
{
	t_node				*current_env_node;
	t_envioroment_var	*current_env_var;

	current_env_node = environment_vars->head;
	while (current_env_node)
	{
		current_env_var = (t_envioroment_var *)current_env_node->value;
		if (ft_strncmp(current_env_var->var_name, name, ft_strlen(name)) == 0)
		{
			return (current_env_var->var_value);
		}
		current_env_node = current_env_node->next;
	}
	return (NULL);
}
char	**get_str_array_from_envioroment_var_list(t_gen_list *envioroment)
{
	t_envioroment_var	*current_env_value;
	t_node				*current_env_node;
	char				**result;
	int					i;
	char				*aux_of_free;

	i = 0;
	result = ft_caalloc(envioroment->size + 1, sizeof(char *));
	printf("%li\n", envioroment->size);
	current_env_node = envioroment->head;
	while (current_env_node != NULL)
	{
		current_env_value = (t_envioroment_var *)current_env_node->value;
		aux_of_free = ft_strjoin(current_env_value->var_name, "=");
		result[i] = ft_strjoin(aux_of_free, current_env_value->var_value);
		free(aux_of_free);
		i++;
		current_env_node = current_env_node->next;
	}
	return (result);
}

void	destroy_envioroment_var(void *envioroment_var)
{
	t_envioroment_var	*aux;

	aux = (t_envioroment_var *)envioroment_var;
	free(aux->var_name);
	free(aux->var_value);
	free(aux);
}
void	change_env_value(t_gen_list *envioroment, char *new_value, char *name)
{
	t_node				*current_node;
	t_envioroment_var	*current_node_value;
	size_t				len;

	len = ft_strlen(name);
	current_node = envioroment->head;
	while (current_node != NULL)
	{
		current_node_value = (t_envioroment_var *)current_node->value;
		if (ft_strncmp(current_node_value->var_name, name, len))
		{
			free(current_node_value->var_value);
			current_node_value->var_value = new_value;
			return ;
		}
		current_node = current_node->next;
	}
}
void	remove_envioroment_var_from_name(t_gen_list *envioroment, char *name)
{
	t_node				*current_node;
	t_envioroment_var	*current_node_value;
	t_node				*last_node;
	size_t				len;

	len = ft_strlen(name);
	current_node = envioroment->head;
	while (current_node != NULL)
	{
		current_node_value = (t_envioroment_var *)current_node->value;
		if (ft_strncmp(current_node_value->var_name, name, len))
		{
			last_node->next = current_node->next;
			destroy_envioroment_var(current_node_value);
			free(current_node);
			return ;
		}
		last_node = current_node;
		current_node = current_node->next;
	}
}
