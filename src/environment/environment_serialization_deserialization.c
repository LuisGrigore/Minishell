/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_serialization_deserialization.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:53:46 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/30 01:54:33 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_internal.h"

static char	*env_var_to_string(void *element)
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
	result = ft_strjoin(name_eq, env_var->var_value);
	free(name_eq);
	return (result);
}

char	**env_serialize(t_gen_list *envioroment)
{
	if (!envioroment)
		return (NULL);
	return (serialize_to_string_array(envioroment, env_var_to_string));
}

t_gen_list	*env_deserialize(char **str_array)
{
	int			i;
	size_t		j;
	t_gen_list	*env_var_list;
	char		**var_str_name_value_split;

	i = 0;
	env_var_list = init_list();
	while (str_array[i])
	{
		var_str_name_value_split = ft_split(str_array[i], '=');
		push_end(env_var_list, init_environment_var(var_str_name_value_split[0],
				var_str_name_value_split[1]));
		free(var_str_name_value_split);
		i++;
	}
	return (env_var_list);
}
