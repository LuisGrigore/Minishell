/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_state.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:39:37 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/12 05:37:15 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_STATE_H
# define MINI_STATE_H

# include "../include/environment.h"

/**
 * @brief Opaque structure representing the shell's state.
 *
 * Contains the current state of the shell including environment variables,
 * last executed command, last opened file, and exit status flags.
 */
typedef struct s_mini_state	t_mini_state;

/**
 * @brief Creates a new shell state instance.
 *
 * Initializes a new shell state with the provided environment variables and
 * command line arguments.
 *
 * @param args Number of command line arguments

	* @param environment_var_str_array Array of environment
		variables in "KEY=VALUE" format
 * @return Pointer to the newly created shell state,
	or NULL on allocation failure
 */
t_mini_state				*mini_state_create(int args,
								char **environment_var_str_array);

/**
 * @brief Destroys a shell state instance and frees all associated resources.
 *
 * @param state Pointer to the shell state to destroy
 */
void						mini_state_destroy(t_mini_state *state);

/**
 * @brief Gets the last executed command.
 *
 * @param state Pointer to the shell state
 * @return String containing the last command executed, or NULL if none
 */
char						*mini_state_get_last_command(t_mini_state *state);

/**
 * @brief Gets the path of the last opened file.
 *
 * Used primarily for error reporting and debugging purposes.
 *
 * @param state Pointer to the shell state
 * @return String containing the path of the last opened file, or NULL if none
 */
char						*mini_state_get_last_opened_file(
								t_mini_state *state);

/**
 * @brief Gets the current environment.
 *
 * @param state Pointer to the shell state
 * @return Pointer to the environment variables structure
 */
t_environment				*mini_state_get_environment(t_mini_state *state);

/**
 * @brief Updates the last executed command.
 *
 * @param state Pointer to the shell state
 * @param command String containing the command being executed
 */
void						mini_state_set_last_command(t_mini_state *state,
								const char *command);

/**
 * @brief Updates the last opened file path.
 *
 * Used to track file operations for error reporting and debugging.
 *
 * @param state Pointer to the shell state
 * @param file_name Path of the file being opened
 */
void						mini_state_set_last_opened_file(t_mini_state *state,
								const char *file_name);

/**
 * @brief Checks if the shell should exit after the current command.
 *
 * Used to handle exit conditions like the 'exit' command or critical errors.
 *
 * @param state Pointer to the shell state
 * @return true if the shell should exit, false otherwise
 */
bool						mini_state_get_exit_after_last_command(
								t_mini_state *state);

/**
 * @brief Sets whether the shell should exit after the current command.
 *
 * @param state Pointer to the shell state
 * @param value true to request shell exit, false to continue execution
 */
void						mini_state_set_exit_after_last_command(
								t_mini_state *state, bool value);
void						mini_state_set_heredoc_temp_file(
								t_mini_state *state, int files);

void						destroy_temp_fles(t_mini_state *state);

#endif