/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_query.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:54:42 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/09 23:07:23 by lgrigore         ###   ########.fr       */
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
