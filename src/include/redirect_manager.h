/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manager.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 05:04:07 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/12 16:19:31 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_MANAGER_H
# define REDIRECT_MANAGER_H
# include "../external/gen_list/gen_list.h"
# include "mini_state.h"

/* ============================================================
**  Data Structures
** ============================================================
*/
/**
 * @enum e_redirect_type
 * @brief Enumeration of possible redirection types.
 *
 * LEFT_REDIRECT          : Input redirection ("<").
 * RIGHT_REDIRECT         : Output redirection (">"), truncates the file.
 * DOUBLE_LEFT_REDIRECT   : Heredoc ("<<"), reads input until a delimiter.
 * DOUBLE_RIGHT_REDIRECT  : Output append redirection (">>").
 * NONE                   : No redirection.
 * ERROR                  : Invalid or unrecognized redirection.
 */
typedef enum e_redirect_type
{
	LEFT_REDIRECT,
	RIGHT_REDIRECT,
	DOUBLE_LEFT_REDIRECT,
	DOUBLE_RIGHT_REDIRECT,
}							t_redirect_type;

/**
 * @struct s_redirect
 * @brief Opaque structure representing a redirection.
 *
 * Contains the redirection type and the target file or heredoc delimiter.
 */
typedef struct s_redirect	t_redirect;

/* ============================================================
**  Lifecycle
** ============================================================
*/

/**
 * @brief Creates a new redirect structure.
 *

 * Allocates and initializes a redirect object with the given type and target.
 * The file name is typically duplicated internally to ensure memory safety.
 *
 * @param redirect_type The type of the redirection (see t_redirect_type).
 * @param file_name The target file name or heredoc delimiter.
 * @return A pointer to the newly created redirect structure,
	or NULL on failure.
 */
t_redirect					*redirect_create(t_redirect_type redirect_type,
								char *file_name);

/**
 * @brief Destroys a redirect structure and frees its memory.
 *
 * Safely releases both the redirect object and its associated file name.
 *
 * @param redirect Pointer to the redirect structure to destroy.
 */
void						redirect_destroy(t_redirect *redirect);

/* ============================================================
**  Operations
** ============================================================
*/

/**
 * @brief Executes a redirection operation.
 *
 *
 * @param redirect Pointer to a t_redirect.
 * @see t_redirect
 *
 * @return
 *         0 if the redirection was executed successfully.
 *        -1 if an error occurred during redirection.
 */
int							redirect_execute(t_redirect *redirect,
								t_mini_state *mini_state);

int							redirect_heredoc_check(t_gen_list *redirects,
								t_mini_state *mini_state);

#endif