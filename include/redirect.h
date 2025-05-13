#ifndef REDIRECT_H
# define REDIRECT_H

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
    struct s_redirect *next;

} t_redirect;



# endif