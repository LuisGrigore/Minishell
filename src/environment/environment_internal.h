/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:52:04 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/09 23:17:25 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_INTERNAL_H
# define ENVIRONMENT_INTERNAL_H

# include "../../external/gen_list/gen_list.h"
# include "../../external/libft/libft.h"
# include "../../include/environment.h"
# include "../include/util.h"
# include <stdlib.h>

typedef struct s_env_var
{
	char		*var_name;
	char		*var_value;
}				t_env_var;

struct			s_environment
{
	t_gen_list	*variables;
};

t_env_var		*init_environment_var(char *name, char *value);
void			destroy_environment_var(void *env_var);
bool			var_name_filter(void *var_ptr, void *context);

#endif
