#include "environment_internal.h"

int add_var(t_gen_list *env, char *name, char *value)
{
    t_environment_var *new_var;
    t_environment_var *found_var;
    char *previous_val;
    
    found_var = (t_environment_var *)find_in_list_ctx(env, var_name_filter, name);
    if (found_var)
    {
        previous_val = found_var->var_value;
        found_var->var_value = ft_strdup(value);
        if (!found_var->var_value)
            return 0;
        free(previous_val);
        return 1;
    }

    new_var = init_environment_var(ft_strdup(name), ft_strdup(value));
    if (!new_var)
        return 0;
    
    push_front(env, (void *)new_var);
    return 1;
}

void	remove_var(t_gen_list *envioroment, char *name)
{
	remove_if_ctx(envioroment, var_name_filter, (void *) name, destroy_environment_var);
}

void destroy_environment(t_gen_list *env)
{
	destroy_gen_list(env, destroy_environment_var);
}
