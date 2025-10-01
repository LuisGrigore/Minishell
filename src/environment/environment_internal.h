/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:52:04 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/01 13:33:54 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_INTERNAL_H
# define ENVIRONMENT_INTERNAL_H

# include "../../include/environment.h"
# include "../../libft/libft.h"
//#include "../../include/util.h"
# include <stdlib.h>

/* ============================================================
**  Internal Environment Variable Structure
** ============================================================
*/

/**
 * @brief Represents a single environment variable (internal use).
 *
 * Stores the name and value of an environment variable.
 *
 * @see t_env_var
 */
struct		s_env_var
{
	char	*var_name;
	char	*var_value;
};

/* ============================================================
**  Internal Helper Functions
** ============================================================
*/

/**
 * @brief Create a new environment variable.
 *
 * Allocates and initializes a new t_env_var with the given name and value.
 *
 * @param name Name of the variable (must not be NULL).
 * @param value Value of the variable (can be NULL for empty).
 * @return Pointer to the newly allocated t_env_var,
	or NULL on allocation failure.
 *
 * @see destroy_environment_var
 */
t_env_var	*init_environment_var(char *name, char *value);

/**
 * @brief Destroy a single environment variable.
 *
 * Frees the name, value, and the structure itself.
 * Designed to be compatible with generic list destruction functions.
 *
 * @param env_var Pointer to the environment variable to destroy.
 *
 * @see init_environment_var
 */
void		destroy_environment_var(void *env_var);

/**
 * @brief Filter function for comparing variable names.
 *
 * Can be used as a callback in list search or remove operations.
 *
 * @param var_ptr Pointer to t_env_var.
 * @param context Pointer to a string with the variable name to match.
 * @return true if names match, false otherwise.
 *
 * @see t_env_var
 */
bool		var_name_filter(void *var_ptr, void *context);

#endif
