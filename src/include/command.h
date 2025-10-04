/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:11 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/04 12:41:06 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include "../external/gen_list/gen_list.h"
# include "../include/redirect_manager.h"

/* ============================================================
**  Data Structures
** ============================================================
*/

/**
 * @brief Represents a command
 * 
 * @see command_create
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
t_command *command_create(char *name);

/**
 * @brief Destroys a command structure and frees memory.
 * 
 * @param command Pointer to the command to destroy.
 */
void command_destroy(t_command *command);

/* ============================================================
**  Command Queries
** ============================================================
*/

bool command_is_built_in(t_command *command);

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
void command_push_arg(t_command *command, char *arg);

/**
 * @brief Adds a redirection to the command.
 * 
 * @param command Pointer to the command.
 * @param redirect_type Type of redirection (input, output, append).
 * @param file_name Target file for the redirection.
 */
void command_push_redirect(t_command *command, t_redirect_type redirect_type, char *file_name);

/**
 * @brief Executes the command with the given environment.
 * 
 * @param command Pointer to the command.
 * @param environment Pointer to the environment variable list.
 * @return 0 on success, -1 on error.
 */
int command_exec(t_command *command, t_gen_list *environment);

/* ============================================================
**  Debug
** ============================================================
*/

void print_command(t_command *cmd, int index);


#endif
