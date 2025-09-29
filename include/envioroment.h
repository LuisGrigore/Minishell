/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envioroment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:29 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/30 00:11:45 by lgrigore         ###   ########.fr       */
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
 */
void remove_var(t_gen_list *env, char *name);

t_gen_list			*deserialize_environment_vars(char **str_array);

char **serialize_environment_vars(t_gen_list *envioroment);

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

void destroy_environment(t_gen_list *env);

#endif
