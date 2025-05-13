#ifndef REDIRECT_H
# define REDIRECT_H
#include "list.h"

typedef enum e_redirect
{ 
    LEFT_REDIRECT,
    RIGHT_REDIRECT,
    DOUBLE_LEFT_REDIRECT,
    DOUBLE_RIGHT_REDIRECT,
    NONE,
    ERROR,
} e_redirect;

typedef struct s_redirect
{
    char *file;
    e_redirect redirect_simbol;
} t_redirect;

t_redirect *init_redirect();
//Comprobar si cada string no empieza por " o '
t_gen_list *get_redirects_from_str_arr(char *str);
void destroy_redirect(t_redirect *redirect);

# endif