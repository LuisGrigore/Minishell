/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:11 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 18:00:12 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include "../external/gen_list/gen_list.h"
# include "mini_state.h"
# include "ms_status_codes.h"
# include "redirect_manager.h"

/* ============================================================
**  Data Structures
** ============================================================
*/

/**
 * @brief Represents a shell command with its arguments and redirections
 *
 * This structure encapsulates all information needed to execute a command,
 * including its name, arguments, and any input/output redirections.
 *
 * @see command_create
 * @see command_destroy
 */
typedef struct s_command	t_command;

/* ============================================================
**  Command Lifecycle
** ============================================================
*/

/**
 * @brief Creates a new command structure.
 *
 * @param name Name of the command.
 * @return Pointer to the newly created command.
 */
t_command					*command_create(char *name);

/**
 * @brief Destroys a command structure and frees memory.
 *
 * @param command Pointer to the command to destroy.
 */
void						command_destroy(t_command *command);

/* ============================================================
**  Command Queries
** ============================================================
*/

/**
 * Checks whether a given command is a built-in shell command.
 *
 * A built-in command is executed directly by the shell.
 *
 * @param command Pointer to a t_command structure representing
 *        the command to be checked.
 *@see t_command
 * @return true if the command is built-in, false otherwise.
 */
bool						command_is_built_in(t_command *command);

/**
 * Retrieves the name of the given command.
 *
 * @param command Pointer to a t_command structure representing
 *        the command whose name should be retrieved.
 *
 * @return A pointer to a null-terminated string containing the
 *         command name. The caller should not modify or free this
 *         string unless explicitly documented in the implementation.
 */
char						*command_get_name(t_command *command);

/* ============================================================
**  Command Operations
** ============================================================
*/

/**
 * @brief Adds an argument to the command.
 *
 * @param command Pointer to the command.
 * @param arg Argument string to add.
 */
int							command_push_arg(t_command *command, char *arg);

/**
 * @brief Adds a redirection to the command.
 *
 * @param command Pointer to the command.
 * @param redirect_type Type of redirection (input, output, append).
 * @param file_name Target file for the redirection.
 */
int							command_push_redirect(t_command *command,
								t_redirect_type redirect_type, char *file_name);

/**
 * @brief Executes the command with the given environment.
 *
 * @param command Pointer to the command.
 * @param environment Pointer to the environment variable list.
 * @return 0 on success, -1 on error.
 */
int							command_exec(t_command *command,
								t_mini_state *mini_state);

int							command_heredocs_create(t_gen_list *commands,
								t_mini_state *mini_state);
int							command_heredocs_asignate(t_gen_list *commands,
								t_mini_state *mini_state);

void	print_command(void *cmd_ptr, void *index_ptr);
void command_set_name(t_command *command, char *name);
#endif
