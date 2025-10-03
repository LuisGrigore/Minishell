/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:38:45 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/03 15:42:00 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_MANAGER_H
#define PIPE_MANAGER_H

#include <stdlib.h>

/**
 * @brief Struct representing a pipe manager for multiple commands.
 */
typedef struct s_pipe_manager t_pipe_manager;

/**
 * @brief Initializes a pipe manager for a given number of commands.
 * 
 * @param n_cmds Number of commands in the pipeline.
 * @return Pointer to the newly created pipe manager.
 */
t_pipe_manager *pipe_manager_init(size_t n_cmds);

/**
 * @brief Destroys a pipe manager and frees its resources.
 * 
 * @param pm Pointer to the pipe manager to destroy.
 */
void pipe_manager_destroy(t_pipe_manager *pm);

/**
 * @brief Sets up the pipes for a specific command in the pipeline.
 * 
 * This function configures the file descriptors for the command at the
 * given index.
 * 
 * @param pm Pointer to the pipe manager.
 * @param index Index of the command in the pipeline.
 */
void pipe_manager_setup_command(t_pipe_manager *pm, size_t index);

/**
 * @brief Closes all pipes managed by the pipe manager.
 * 
 * @param pm Pointer to the pipe manager.
 */
void pipe_manager_close_all(t_pipe_manager *pm);

#endif