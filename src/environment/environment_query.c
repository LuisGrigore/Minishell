/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_query.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:54:42 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 20:49:39 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_internal.h"

bool	env_has(t_environment *env, char *name)
{
	if (!env || !env->variables)
		return (false);
	return (gen_list_has_ctx(env->variables, var_name_filter, name));
}

char	*env_get(t_environment *env, char *name)
{
	t_env_var	*found_var;

	if (!env || !env->variables)
		return (NULL);
	found_var = (t_env_var *)gen_list_find_ctx(env->variables, var_name_filter,
			name);
	if (!found_var)
		return (NULL);
	return (ft_strdup(found_var->var_value));
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

char	**env_serialize_export(t_environment *env)
{
	if (!env || !env->variables)
		return (NULL);
	return (gen_list_serialize_to_string_array(env->variables,
			env_var_to_string_export));
}
