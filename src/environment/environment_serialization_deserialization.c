#include "environment_internal.h"

static char *env_var_to_string(void *element)
{
    t_environment_var *env_var = (t_environment_var *)element;
    if (!env_var)
        return NULL;

    char *name_eq = ft_strjoin(env_var->var_name, "=");
    if (!name_eq)
        return NULL;

    char *result = ft_strjoin(name_eq, env_var->var_value);
    free(name_eq);

    return result;
}

char **serialize_environment_vars(t_gen_list *envioroment)
{
	if (!envioroment)
		return(NULL);
	return (serialize_to_string_array(envioroment, env_var_to_string));
}

t_gen_list	*deserialize_environment_vars(char **str_array)
{
	int			i;
	size_t			j;
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