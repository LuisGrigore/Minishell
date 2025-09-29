/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envioroment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:29 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/29 16:09:10 by lgrigore         ###   ########.fr       */
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

/**
 * @brief Adds a new variable to the env list or modifies its value if the variable already exists.
 *
 * @param env Environment variable list.
 * @param name Name of the variable.
 * @param value Value of the variable.
 * @return 1 if success, error otherwhise. 
 */
int add_var(t_gen_list *env, char *name, char *value);
/**
 * @brief Removes a variable with the given name from the env list.
 *
 * @param env Environment variable list.
 * @param name Name of the variable.
 * @return 1 if success, error otherwhise. 
 */
int remove_var(t_gen_list *env, char *name);

t_envioroment_var	*init_envioroment_var(char *name, char *value);
t_gen_list			*get_environment_var_list_from_str_array(char **str_array);
char				**get_str_array_from_envioroment_var_list(t_gen_list *envioroment);

/**
 * @brief Gets the value of an environment variable given its name.
 * 		
 *This function returns a copy of the value of the variable in case of success, it needs to be freed;
 * @param env Environment variable list.
 * @param name Name of the variable.
 * @return Copy of value if success, NULL if error. 
 */
char				*get_var_value(t_gen_list *environment_vars,
						char *name);
/**
 * @brief Checks if the env list contains a variable with the given name.
 * 		
 * @param environment_vars Environment variable list.
 * @param name Name of the variable.
 * @return True if contains, false if not. 
 */
bool contains_variable(t_gen_list *environment_vars, char *name);
void				destroy_envioroment_var(void *envioroment_var);
void				change_env_value(t_gen_list *envioroment, char *new_value,
						char *name);
void				remove_envioroment_var_from_name(t_gen_list *envioroment,
						char *name);

#endif
