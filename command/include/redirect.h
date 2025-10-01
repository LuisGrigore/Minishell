#ifndef REDIRECT_ASIGNATION_H
# define REDIRECT_ASIGNATION_H
# include "../external/gen_list/gen_list.h"

typedef enum e_redirect_type
{
	LEFT_REDIRECT,
	RIGHT_REDIRECT,
	DOUBLE_LEFT_REDIRECT,
	DOUBLE_RIGHT_REDIRECT,
	NONE,
	ERROR,
}					t_redirect_type;

typedef struct s_redirect
{
	char			*file;
	t_redirect_type	redirect_simbol;
}					t_redirect;

t_redirect			*init_redirect(char *file, t_redirect_type redirect_type);
t_gen_list			*get_redirects_from_str_arr(char *str);
void				destroy_redirect(void *redirect);

#endif