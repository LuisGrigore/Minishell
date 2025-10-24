/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:52:55 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/24 06:06:28 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_internal.h"

int	env_set(t_gen_list *env, char *name, char *value)
{
	t_env_var	*new_var;
	t_env_var	*found_var;
	char		*previous_val;

	found_var = (t_env_var *)gen_list_find_ctx(env, var_name_filter, name);
	if (found_var)
	{
		previous_val = found_var->var_value;
		found_var->var_value = ft_strdup(value);
		if (!found_var->var_value)
			return (MS_ALLOCATION_ERR);
		free(previous_val);
		return (MS_OK);
	}

	new_var = init_environment_var(ft_strdup(name), ft_strdup(value));
	if (!new_var)
		return (MS_ALLOCATION_ERR);
	gen_list_push_front(env, (void *)new_var);
	return (MS_OK);
}

void	env_unset(t_gen_list *envioroment, char *name)
{
	t_env_var *found;

	found = (t_env_var *)gen_list_find_ctx(envioroment, var_name_filter, name);
	gen_list_remove_if_ctx(envioroment, var_name_filter, (void *)name,
		destroy_environment_var);
}

void	env_destroy(t_gen_list *env)
{
	gen_list_destroy(env, destroy_environment_var);
}
