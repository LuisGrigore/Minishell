/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envioroment_operations_b.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:56:24 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/12 04:57:04 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_internal.h"

int	env_get_last_status_code(t_environment *env)
{
	char	*status_code_str;
	int		status_code;

	status_code_str = env_get(env, "?");
	if (!status_code_str)
		return (0);
	status_code = ft_atoi(status_code_str);
	free(status_code_str);
	return (status_code);
}

void	env_unset(t_environment *env, char *name)
{
	if (!env || !env->variables)
		return ;
	gen_list_remove_if_ctx(env->variables, var_name_filter, (void *)name,
		destroy_environment_var);
}

void	env_destroy(t_environment *env)
{
	if (!env)
		return ;
	if (env->variables)
		gen_list_destroy(env->variables, destroy_environment_var);
	free(env);
}
