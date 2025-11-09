/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:29 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/09 16:10:21 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "../external/gen_list/gen_list.h"
# include <stdbool.h>
#include "ms_status_codes.h"


/* ============================================================
**  Data Structures
** ============================================================
*/

/**
 * @brief Represents a single environment variable.
 *
 * Each environment variable consists of a name and its associated value.
 */
typedef struct s_env_var	t_env_var;

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
 * @param name Name of the variable (must not be NULL).
 * @param value Value of the variable (can be NULL for empty).
 * @return 1 on success, or an error code otherwise.
 *
 * @see env_unset
 * @see env_get
 * @see env_has
 * @see t_env_var
 */
int							env_set(t_gen_list *env, char *name, char *value);
void env_set_last_status_code(t_gen_list *env, int status_code);
int env_get_last_status_code(t_gen_list *env);

/**
 * @brief Remove an environment variable by name.
 *
 * If the variable is found, it is removed from the list.
 *
 * @param env Environment variable list.
 * @param name Name of the variable to remove.
 *
 * @see env_set
 * @see env_get
 * @see env_has
 * @see t_env_var
 */
void						env_unset(t_gen_list *env, char *name);

/**
 * @brief Destroy the entire environment list and free resources.
 *
 * Frees all variables, their names and values, then frees the list itself.
 *
 * @param env Environment variable list.
 *
 * @see env_set
 * @see env_unset
 * @see t_env_var
 */
void						env_destroy(t_gen_list *env);

/* ============================================================
**  Serialization / Deserialization
** ============================================================
*/

/**
 * @brief Serialize environment variables into a null-terminated string array.
 *
 * Each environment variable is represented as "NAME=VALUE".
 *
 * @param env Environment variable list.
 * @return Dynamically allocated null-terminated array of strings,
 *         or NULL on allocation failure.
 *
 * @see env_deserialize
 * @see t_env_var
 */
char						**env_serialize(t_gen_list *env);

/**
 * @brief Convert a string array into an environment variable list.
 *
 * Each string must follow the "NAME=VALUE" format.
 *
 * @param str_array Null-terminated array of strings.
 * @return Pointer to a newly allocated environment variable list,
 *         or NULL on error.
 *
 * @see env_serialize
 * @see t_env_var
 */
t_gen_list					*env_deserialize(char **str_array);

/* ============================================================
**  Query Functions
** ============================================================
*/

/**
 * @brief Get the value of an environment variable by name.
 *
 * The returned value is a newly allocated copy and must be freed by the caller.
 *
 * @param env Environment variable list.
 * @param name Name of the variable to search.
 * @return Dynamically allocated copy of the value, or NULL if not found.
 *
 * @see env_set
 * @see env_unset
 * @see env_has
 * @see t_env_var
 */
char						*env_get(t_gen_list *env, char *name);

/**
 * @brief Check if an environment variable exists by name.
 *
 * @param env Environment variable list.
 * @param name Name of the variable.
 * @return true if the variable exists, false otherwise.
 *
 * @see env_set
 * @see env_unset
 * @see env_get
 * @see t_env_var
 */
bool						env_has(t_gen_list *env, char *name);

/**
 * Expands environment variables in a given string.
 *
 * This function scans the input `line` for environment variable references
 * prefixed with `$` and replaces them with their corresponding values from
 * the provided environment list `env`. The resulting string preserves other
 * characters as-is and handles multiple variable expansions in the same line.
 *
 * Example:
 *   If `line` is "Hello $USER" and the environment has USER="Alice",
 *   the function will return "Hello Alice".
 *
 * @param env Pointer to a t_env_var list representing the environment.
 * @see t_env_var
 *
 * @param line Pointer to a null-terminated string that may contain
 *             environment variable references to expand.
 *
 * @return A newly allocated string with all recognized environment variables
 *         expanded. Returns NULL if `line` is NULL. The caller is responsible
 *         for freeing the returned string.
 *
 * @note This function handles only simple variable expansions (e.g., $VAR)
 *       and does not process complex shell syntax like ${VAR}.
 */
char *env_expand_vars(t_gen_list *env, char *line);

#endif
