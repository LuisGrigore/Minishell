/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envioroment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:35:48 by dmaestro          #+#    #+#             */
/*   Updated: 2025/05/10 17:35:50 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envioroment.h"
#include "../include/list.h"
#include "../libft/libft.h"
#include "stdlib.h"
#include <stdio.h>

t_envioroment_var *init_envioroment_var()
{
    t_envioroment_var *new_env = ft_calloc(1, sizeof(t_envioroment_var));

    new_env->var_name = NULL;
    new_env->var_value = NULL;
    return(new_env);
}

t_envioroment_var *init_envioroment_var_name_value(char *name, char *value)
{
    t_envioroment_var *new_env = init_envioroment_var();

    new_env->var_name = name;
    new_env->var_value = value;
    return(new_env);
}

t_gen_list *get_environment_var_list_from_str_array(char **str_array)
{
    int i = 0;
    t_gen_list *env_var_list = init_list();
    char **var_str_name_value_split;
    while(str_array[i])
    {
        var_str_name_value_split = ft_split(str_array[i], '=');
        insert_end(env_var_list, init_envioroment_var_name_value(var_str_name_value_split[0], var_str_name_value_split[1]));
        i++;
    }
    return (env_var_list);
}

char *get_var_value_from_name(t_gen_list *environment_vars, char *name)
{
    int i = 0;
    t_node *current_env_node = environment_vars->head;
    t_envioroment_var *current_env_var;
    while(current_env_node)
    {
        current_env_var = (t_envioroment_var*) current_env_node->value;
        if(ft_strncmp(current_env_var->var_name, name, ft_strlen(name)) == 0)
        {
            return  current_env_var->var_value;
        }
        current_env_node = current_env_node->next;
    }
    return (NULL);
}

void destroy_envioroment_var(t_envioroment_var *envioroment_var)
{
    free(envioroment_var->var_name);
    free(envioroment_var->var_value);
    free(envioroment_var);
}

