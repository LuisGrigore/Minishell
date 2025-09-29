/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:52:55 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/30 01:52:56 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_internal.h"

int	env_set(t_gen_list *env, char *name, char *value)
{
	t_env_var	*new_var;
	t_env_var	*found_var;
	char		*previous_val;

	found_var = (t_env_var *)find_in_list_ctx(env, var_name_filter, name);
	if (found_var)
	{
		previous_val = found_var->var_value;
		found_var->var_value = ft_strdup(value);
		if (!found_var->var_value)
			return (0);
		free(previous_val);
		return (1);
	}
	new_var = init_environment_var(ft_strdup(name), ft_strdup(value));
	if (!new_var)
		return (0);
	push_front(env, (void *)new_var);
	return (1);
}

void	env_unset(t_gen_list *envioroment, char *name)
{
	remove_if_ctx(envioroment, var_name_filter, (void *)name,
		destroy_environment_var);
}

void	env_destroy(t_gen_list *env)
{
	destroy_gen_list(env, destroy_environment_var);
}
