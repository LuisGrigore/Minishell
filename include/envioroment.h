/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envioroment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:29 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/29 00:19:44 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIOROMENT_H
# define ENVIOROMENT_H

#include "../list/list.h"

typedef struct s_envioroment_var
{
	char			*var_name;
	char			*var_value;
}					t_envioroment_var;

t_envioroment_var	*init_envioroment_var(char *name, char *value);
t_gen_list			*get_environment_var_list_from_str_array(char **str_array);
char				**get_str_array_from_envioroment_var_list(t_gen_list *envioroment);
char				*get_var_value_from_name(t_gen_list *environment_vars,
						char *name);
void				destroy_envioroment_var(void *envioroment_var);
void				change_env_value(t_gen_list *envioroment, char *new_value,
						char *name);
void				remove_envioroment_var_from_name(t_gen_list *envioroment,
						char *name);

#endif
