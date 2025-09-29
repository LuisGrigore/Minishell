/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_query.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:54:42 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/30 01:55:24 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_internal.h"

bool	env_has(t_gen_list *environment_vars, char *name)
{
	return (contains_in_list_ctx(environment_vars, var_name_filter, name));
}

char	*env_get(t_gen_list *environment_vars, char *name)
{
	t_env_var	*found_var;

	found_var = find_in_list_ctx(environment_vars, var_name_filter, name);
	if (!found_var)
		return (NULL);
	return (ft_strdup(found_var->var_value));
}
