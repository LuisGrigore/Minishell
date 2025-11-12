/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_operations_a.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:52:55 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/12 04:56:16 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_internal.h"

t_environment	*env_create(void)
{
	t_environment	*env;

	env = ft_calloc(1, sizeof(t_environment));
	if (!env)
		return (NULL);
	env->variables = gen_list_create();
	if (!env->variables)
	{
		free(env);
		return (NULL);
	}
	return (env);
}

int	env_set(t_environment *env, char *name, char *value)
{
	t_env_var	*new_var;
	t_env_var	*found_var;
	char		*previous_val;

	if (!env || !env->variables)
		return (MS_ALLOCATION_ERR);
	found_var = (t_env_var *)gen_list_find_ctx(env->variables, var_name_filter,
			name);
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
	gen_list_push_front(env->variables, (void *)new_var);
	return (MS_OK);
}

void	env_set_last_status_code(t_environment *env, int status_code)
{
	char	*status_code_str;

	status_code_str = ft_itoa(status_code);
	env_set(env, "?", status_code_str);
	free(status_code_str);
}
