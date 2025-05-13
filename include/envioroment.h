

#ifndef ENVIOROMENT_H
# define ENVIOROMENT_H

typedef struct s_envioroment_var
{
    char *var_name;
    char *var_value;
}   t_envioroment_var;

t_envioroment_var *init_envioroment_var();
t_gen_list *get_environment_var_lit_from_str_array(char **str_array);
char *get_var_value_from_name(t_gen_list *environment_vars, char *name);
void destroy_envioroment_var(t_envioroment_var *envioroment_var);

# endif
