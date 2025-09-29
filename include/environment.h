/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:29 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/30 01:20:47 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdbool.h>
# include "../list/list.h"

/* ============================================================
**  Data Structures
** ============================================================
*/

/**
 * @brief Represents a single environment variable.
 *
 * Each environment variable consists of a name and its associated value.
 */
typedef struct s_environment_var t_environment_var;

/* ============================================================
**  Environment Operations
** ============================================================
*/

/**
 * @brief Add or update an environment variable.
 *
 * If the variable does not exist, it is created and added to the list.
 * If the variable already exists, its value is updated.
 *
 * @param env Environment variable list.
 * @param name Name of the variable.
 * @param value Value of the variable.
 * @return 1 on success, or an error code otherwise.
 */
int			add_var(t_gen_list *env, char *name, char *value);

/**
 * @brief Remove an environment variable by name.
 *
 * If the variable is found, it is removed from the list.
 *
 * @param env Environment variable list.
 * @param name Name of the variable to remove.
 */
void		remove_var(t_gen_list *env, char *name);

/**
 * @brief Destroy the entire environment list and free resources.
 *
 * Frees all variables and their names/values, then frees the list.
 *
 * @param env Environment variable list.
 */
void		destroy_environment(t_gen_list *env);

/* ============================================================
**  Serialization / Deserialization
** ============================================================
*/

/**
 * @brief Serialize environment variables into a null-terminated string array.
 *
 * Each environment variable is represented as "NAME=VALUE".
 *
 * @param envioroment Environment variable list.
 * @return Dynamically allocated null-terminated array of strings.
 */
char		**serialize_environment_vars(t_gen_list *envioroment);

/**
 * @brief Convert a string array into an environment variable list.
 *
 * Each string must follow the "NAME=VALUE" format.
 *
 * @param str_array Null-terminated array of strings.
 * @return Pointer to a newly allocated environment variable list,
 *         or NULL on error.
 */
t_gen_list	*deserialize_environment_vars(char **str_array);

/* ============================================================
**  Query Functions
** ============================================================
*/

/**
 * @brief Get the value of an environment variable by name.
 *
 * The returned value is a copy and must be freed by the caller.
 *
 * @param environment_vars Environment variable list.
 * @param name Name of the variable to search.
 * @return Dynamically allocated copy of the value, or NULL if not found.
 */
char		*get_var_value(t_gen_list *environment_vars, char *name);

/**
 * @brief Check if an environment variable exists by name.
 *
 * @param environment_vars Environment variable list.
 * @param name Name of the variable.
 * @return true if the variable exists, false otherwise.
 */
bool		contains_variable(t_gen_list *environment_vars, char *name);

#endif
