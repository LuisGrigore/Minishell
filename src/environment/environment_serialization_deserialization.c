/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_serialization_deserialization.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:53:46 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/09 21:43:27 by lgrigore         ###   ########.fr       */
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

static char **split_var(char *var)
{
	int i;
	char **resul;
	size_t len;

	if (!var)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	resul = malloc(sizeof(char *) * 3);
	if (!resul)
		return (NULL);
	while (var[i] && var[i] != '=')
		i++;
	resul[0] = ft_substr(var, 0, i);
	if (!resul[0])
	{
		free(resul);
		return (NULL);
	}
	if (i < (int)len && var[i] == '=')
		resul[1] = ft_substr(var, i + 1, len - i - 1);
	else
		resul[1] = ft_strdup("");
	if (!resul[1])
	{
		free(resul[0]);
		free(resul);
		return (NULL);
	}
	resul[2] = NULL;
	return (resul);
}

t_gen_list	*env_deserialize(char **str_array)
{
	t_gen_list	*env_var_list;
	char		**split;
	t_env_var	*env;
	size_t		i;

	if (!str_array)
		return (NULL);
	env_var_list = gen_list_create();
	if (!env_var_list)
		return (NULL);
	i = 0;
	while (str_array[i])
	{
		split = simple_split(str_array[i], '=');
		if (!split)
		{
			i++;
			continue ;
		}
		env = init_environment_var(split[0], split[1]);
		if (env)
			gen_list_push_back(env_var_list, env);
		else
			free_double_pointer(split);
		
		free(split);
		i++;
	}
	env_set(env_var_list, "?", "0");
	return (env_var_list);
}
