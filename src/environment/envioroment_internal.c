/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envioroment_internal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:35:48 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/01 13:05:48 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "environment_internal.h"
#include <stdlib.h>

bool	var_name_filter(void *var_ptr, void *context)
{
	char		*name;
	t_env_var	*var;
	size_t		name_size;

	name = (char *)context;
	var = (t_env_var *)var_ptr;
	name_size = ft_strlen(name);
	if (ft_strlen(var->var_name) == name_size && ft_strncmp(var->var_name, name,
			name_size) == 0)
		return (true);
	return (false);
}

t_env_var	*init_environment_var(char *name, char *value)
{
	t_env_var	*new_env;

	new_env = ft_calloc(1, sizeof(t_env_var));
	if (new_env == NULL)
		return (NULL);
	new_env->var_name = name;
	new_env->var_value = value;
	return (new_env);
}

void	destroy_environment_var(void *envioroment_var)
{
	t_env_var	*aux;

	if (!envioroment_var)
		return;
	aux = (t_env_var *)envioroment_var;
	free(aux->var_name);
	free(aux->var_value);
	free(aux);
}
