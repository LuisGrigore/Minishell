/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:38:45 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/06 14:02:59 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_MANAGER_H
#define PIPE_MANAGER_H

#include <stdlib.h>
#include "ms_status_codes.h"

#define PIPE_MANAGER_STATUS_BEGIN 700

typedef enum e_pipe_manager_status_code
{
	PIPE_MANAGER_IS_NULL = PIPE_MANAGER_STATUS_BEGIN,
	PIPE_MANAGER_MALFORMED
} t_pipe_manager_status_code;

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
int pipe_manager_setup_command(t_pipe_manager *pm, size_t index);

/**
 * @brief Closes all pipes managed by the pipe manager.
 * 
 * @param pm Pointer to the pipe manager.
 */
int pipe_manager_close_all(t_pipe_manager *pm);

#endif