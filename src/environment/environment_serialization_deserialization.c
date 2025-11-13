/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_serialization_deserialization.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:53:46 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 19:03:01 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_internal.h"

static char	*env_var_to_string_env(void *element)
{
	t_env_var	*env_var;
	char		*name_eq;
	char		*result;

	env_var = (t_env_var *)element;
	if (!env_var)
		return (NULL);
	name_eq = ft_strjoin(env_var->var_name, "=");
	if (!name_eq)
		return (NULL);
	if (!env_var->var_value)
		return (free(name_eq), NULL);
	result = ft_strjoin(name_eq, env_var->var_value);
	free(name_eq);
	return (result);
}

static char	*env_var_to_string_export(void *element)
{
	t_env_var	*env_var;
	char		*name_eq;
	char		*result;
	char		*declare;

	env_var = (t_env_var *)element;
	if (!env_var)
		return (NULL);
	declare = ft_strdup("declare -x ");
	name_eq = ft_strjoin(declare, env_var->var_name);
	free(declare);
	if (!name_eq)
		return (NULL);
	if (!env_var->var_value)
		return (name_eq);
	result = ft_strjoin(name_eq, "=\"");
	free(name_eq);
	name_eq = ft_strjoin(result, env_var->var_value);
	free(result);
	result = ft_strjoin(name_eq, "\"");
	return (free(name_eq), result);
}

char	**env_serialize_env(t_environment *env)
{
	if (!env || !env->variables)
		return (NULL);
	return (gen_list_serialize_to_string_array(env->variables,
			env_var_to_string_env));
}

char	**env_serialize_export(t_environment *env)
{
	if (!env || !env->variables)
		return (NULL);
	return (gen_list_serialize_to_string_array(env->variables,
			env_var_to_string_export));
}

static void	env_loop_asignation(char **str_array, t_environment *env)
{
	char		**split;
	t_env_var	*env_var;
	size_t		i;

	i = 0;
	while (str_array[i])
	{
		split = simple_split(str_array[i], '=');
		if (!split)
		{
			i++;
			continue ;
		}
		env_var = init_environment_var(split[0], split[1]);
		if (env_var)
			gen_list_push_back(env->variables, env_var);
		else
			free_double_pointer(split);
		free(split);
		i++;
	}
}

t_environment	*env_deserialize(char **str_array)
{
	t_environment	*env;

	if (!str_array)
		return (NULL);
	env = env_create();
	if (!env)
		return (NULL);
	env_loop_asignation(str_array, env);
	env_set(env, "?", "0");
	return (env);
}
