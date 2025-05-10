

#ifndef ENVIOROMENT_H
# define ENVIOROMENT_H

typedef struct s_envioroment
{
    char *path;
    struct  s_envioroment *next;
}   t_envioroment;

t_envioroment *init_env();
char **env_to_dbarray(t_envioroment *envioroment);
void env_to_list(char **env, t_envioroment *envioroment);
int size_of_env(t_envioroment *fst);
void env_destroyer(t_envioroment *fst);

# endif
