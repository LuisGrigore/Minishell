#ifndef REDIRECT_H
# define REDIRECT_H

typedef enum e_redirect
{ 
    LEFT_REDIRECT,
    RIGHT_REDIRECT,
    DOUBLE_LEFT_REDIRECT,
    DOUBLE_RIGHT_REDIRECT
} e_redirect;

typedef struct s_redirect
{
    int input;
    int output;
    e_redirect redirect;

} t_redirect;

#endif