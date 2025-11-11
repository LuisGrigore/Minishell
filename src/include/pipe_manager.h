/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:38:45 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/09 23:36:14 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_MANAGER_H
# define PIPE_MANAGER_H

# include "../config.h"
# include "ms_status_codes.h"
# include <stdlib.h>

/**
 * @brief Manages pipe connections between multiple commands
 *
 * Handles the creation, setup, and cleanup of pipes for command chains.
 * Ensures proper file descriptor management and data flow between
 * piped commands.
 */
typedef struct s_pipe_manager	t_pipe_manager;

/**
 * @brief Creates a new pipe manager for a command pipeline
 *
 * Allocates and initializes all necessary pipes for a chain of commands.
 * The number of pipes created will be n_cmds - 1.
 *
 * @param n_cmds Number of commands that will be connected by pipes
 * @return New pipe manager instance, or NULL if allocation fails
 *
 * @see pipe_manager_destroy
 */
t_pipe_manager					*pipe_manager_init(size_t n_cmds);

/**
 * @brief Cleans up pipe manager resources
 *
 * Closes all pipe file descriptors and frees allocated memory.
 * Should be called after pipeline execution is complete.
 *
 * @param pm Pipe manager to destroy
 */
void							pipe_manager_destroy(t_pipe_manager *pm);

/**
 * @brief Configures pipes for a command in the pipeline
 *
 * Sets up input/output file descriptors for the command at the given index.
 * For commands in the middle of the pipeline, connects input to the previous
 * command's output and output to the next command's input.
 *
 * @param pm Pipe manager instance
 * @param index Position of the command in the pipeline (0-based)
 * @return 0 on success, or error code on failure
 *
 * @see ms_status_codes.h
 */
int								pipe_manager_setup_command(t_pipe_manager *pm,
									size_t index);

/**
 * @brief Closes all pipe file descriptors
 *
 * Should be called in the parent process after forking all child processes
 * to prevent file descriptor leaks.
 *
 * @param pm Pipe manager instance
 * @return 0 on success, or error code on failure
 *
 * @see ms_status_codes.h
 */
int								pipe_manager_close_all(t_pipe_manager *pm);

#endif