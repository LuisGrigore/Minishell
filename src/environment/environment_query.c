#include "environment_internal.h"


bool contains_variable(t_gen_list *environment_vars, char *name)
{
	return (contains_in_list_ctx(environment_vars,var_name_filter, name));
}

char	*get_var_value(t_gen_list *environment_vars, char *name)
{
	t_environment_var	*found_var;
	found_var = find_in_list_ctx(environment_vars, var_name_filter, name);
	if(!found_var)
		return (NULL);
	return (ft_strdup(found_var->var_value));
}