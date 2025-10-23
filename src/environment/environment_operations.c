/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:52:55 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/23 17:20:23 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_internal.h"
#include <stdio.h>

int	env_set(t_gen_list *env, char *name, char *value)
{
	t_env_var	*new_var;
	t_env_var	*found_var;
	char		*previous_val;

	fprintf(stderr, "DBG-env_set: enter name='%s' value='%s'\n", name ? name : "(null)", value ? value : "(null)");

	found_var = (t_env_var *)gen_list_find_ctx(env, var_name_filter, name);
	if (found_var)
	{
		previous_val = found_var->var_value;
		fprintf(stderr, "DBG-env_set: found existing var name='%s' old_value='%s'\n", name, previous_val ? previous_val : "(null)");
		found_var->var_value = ft_strdup(value);
		if (!found_var->var_value)
			return (MS_ALLOCATION_ERR);
		fprintf(stderr, "DBG-env_set: updated var name='%s' new_value='%s'\n", name, found_var->var_value);
		free(previous_val);
		return (MS_OK);
	}

	new_var = init_environment_var(ft_strdup(name), ft_strdup(value));
	if (!new_var)
		return (MS_ALLOCATION_ERR);
	fprintf(stderr, "DBG-env_set: creating new var name='%s' value='%s'\n", new_var->var_name ? new_var->var_name : "(null)", new_var->var_value ? new_var->var_value : "(null)");
	gen_list_push_front(env, (void *)new_var);
	return (MS_OK);
}

void	env_unset(t_gen_list *envioroment, char *name)
{
	t_env_var *found;

	fprintf(stderr, "DBG-env_unset: remove request name='%s'\n", name ? name : "(null)");
	found = (t_env_var *)gen_list_find_ctx(envioroment, var_name_filter, name);
	if (found)
		fprintf(stderr, "DBG-env_unset: var found, proceeding to remove name='%s' value='%s'\n", name, found->var_value ? found->var_value : "(null)");
	else
		fprintf(stderr, "DBG-env_unset: var not found name='%s'\n", name ? name : "(null)");

	gen_list_remove_if_ctx(envioroment, var_name_filter, (void *)name,
		destroy_environment_var);
}

void	env_destroy(t_gen_list *env)
{
	fprintf(stderr, "DBG-env_destroy: destroying environment list\n");
	gen_list_destroy(env, destroy_environment_var);
}
