/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envioroment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:35:48 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/30 00:11:26 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"
#include "../include/envioroment.h"
#include "../libft/libft.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdlib.h>

static bool var_name_filter(void *var_ptr, void *context)
{
    char *name = (char *)context;
    t_envioroment_var *var = (t_envioroment_var *)var_ptr;
	size_t name_size = ft_strlen(name);
    if (ft_strlen(var->var_name) == name_size && ft_strncmp(var->var_name, name, name_size) == 0)
        return true;
    return false;
}

t_envioroment_var	*init_envioroment_var(char *name, char *value)
{
	t_envioroment_var	*new_env;

	new_env = ft_calloc(1, sizeof(t_envioroment_var));
	if (new_env == NULL)
	return NULL;
	new_env->var_name = name;
	new_env->var_value = value;
	return (new_env);
}

int add_var(t_gen_list *env, char *name, char *value)
{
    t_envioroment_var *new_var;
    t_envioroment_var *found_var;
    char *previous_val;
    
    found_var = (t_envioroment_var *)find_in_list_ctx(env, var_name_filter, name);
    if (found_var)
    {
        previous_val = found_var->var_value;
        found_var->var_value = ft_strdup(value);
        if (!found_var->var_value)
            return 0;
        free(previous_val);
        return 1;
    }

    new_var = init_envioroment_var(ft_strdup(name), ft_strdup(value));
    if (!new_var)
        return 0;
    
    push_front(env, (void *)new_var);
    return 1;
}

static char *env_var_to_string(void *element)
{
    t_envioroment_var *env_var = (t_envioroment_var *)element;
    if (!env_var)
        return NULL;

    char *name_eq = ft_strjoin(env_var->var_name, "=");
    if (!name_eq)
        return NULL;

    char *result = ft_strjoin(name_eq, env_var->var_value);
    free(name_eq);

    return result;
}

char **serialize_environment_vars(t_gen_list *envioroment)
{
	if (!envioroment)
		return(NULL);
	return (serialize_to_string_array(envioroment, env_var_to_string));
}

t_gen_list	*deserialize_environment_vars(char **str_array)
{
	int			i;
	size_t			j;
	t_gen_list	*env_var_list;
	char		**var_str_name_value_split;

	i = 0;
	env_var_list = init_list();
	while (str_array[i])
	{
		var_str_name_value_split = ft_split(str_array[i], '=');
		push_end(env_var_list, init_envioroment_var(var_str_name_value_split[0],
				var_str_name_value_split[1]));
		free(var_str_name_value_split);
		i++;
	}
	return (env_var_list);
}


bool contains_variable(t_gen_list *environment_vars, char *name)
{
	return (contains_in_list_ctx(environment_vars,var_name_filter, name));
}

char	*get_var_value(t_gen_list *environment_vars, char *name)
{
	t_envioroment_var	*found_var;
	found_var = find_in_list_ctx(environment_vars, var_name_filter, name);
	if(!found_var)
		return (NULL);
	return (ft_strdup(found_var->var_value));
}


static void	destroy_envioroment_var(void *envioroment_var)
{
	t_envioroment_var	*aux;

	aux = (t_envioroment_var *)envioroment_var;
	free(aux->var_name);
	free(aux->var_value);
	free(aux);
}

void	remove_var(t_gen_list *envioroment, char *name)
{
	remove_if_ctx(envioroment, var_name_filter, (void *) name, destroy_envioroment_var);
}

void destroy_environment(t_gen_list *env)
{
	destroy_gen_list(env, destroy_envioroment_var);
}
