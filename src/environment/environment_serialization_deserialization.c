/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_serialization_deserialization.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:53:46 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/06 17:09:25 by dmaestro         ###   ########.fr       */
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
	return (gen_list_serialize_to_string_array(envioroment, env_var_to_string));
}

t_gen_list	*env_deserialize(char **str_array)
{
	t_gen_list	*env_var_list;
	char		**split;
	t_env_var	*env;
	size_t		i;

	size_t		j;

	if (!str_array)
		return (NULL);
	env_var_list = gen_list_create();
	if (!env_var_list)
		return (NULL);
	i = 0;
	while (str_array[i])
	{
		split = ft_split(str_array[i], '=');
		if (!split)
		{
			i++;
			continue ;
		}
		env = init_environment_var(split[0], split[1]);
		if (env)
		{
			gen_list_push_back(env_var_list, env);
		}
		else
		{
			j = 0;
			while (split[j])
			{
				free(split[j]);
				j++;
			}
		}
		j = 0;
		while (split[j])
		{
			if (j > 1)
				free(split[j]);
			j++;
		}
		free(split);
		i++;
	}
	env_set(env_var_list, "?", "0");
	return (env_var_list);
}
