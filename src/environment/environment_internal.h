#ifndef ENVIRONMENT_INTERNAL
#define ENVIRONMENT_INTERNAL

#include "../../include/environment.h"
#include "../../libft/libft.h"
#include <stdlib.h>

struct s_environment_var
{
	char	*var_name;
	char	*var_value;
};

t_environment_var	*init_environment_var(char *name, char *value);
void	destroy_environment_var(void *envioroment_var);
bool var_name_filter(void *var_ptr, void *context);

#endif