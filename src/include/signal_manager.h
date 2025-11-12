/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:06:18 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/12 23:27:42 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MANAGER_H
# define SIGNAL_MANAGER_H

# include "ms_status_codes.h"
# include <signal.h>
# include <unistd.h>

/**
 * @brief Sets up signal handlers for interactive shell mode
 *
 * Configures signal handling for the main shell prompt:
 * - SIGINT (Ctrl+C): Interrupts current line, displays new prompt
 * - SIGQUIT (Ctrl+\): Ignored
 * - SIGTSTP (Ctrl+Z): Ignored
 *
 * @return 0 on success, error code on failure
 * @see ms_status_codes.h
 */
int	signals_init_interactive(void);

/**
 * @brief Sets up signal handlers for heredoc input mode
 *
 * Configures special signal handling while reading heredoc input:
 * - SIGINT (Ctrl+C): Cancels heredoc input
 * - SIGQUIT (Ctrl+\): Ignored
 * - SIGTSTP (Ctrl+Z): Ignored
 *
 * @return 0 on success, error code on failure
 * @see ms_status_codes.h
 */
int	signals_init_heredoc(void);

/**
 * @brief Restores default signal handling
 *
 * Resets signal handlers to their original configuration.
 * Should be called:
 * - Before executing external commands
 * - After heredoc input is complete
 * - Before shell exit
 *
 * @return 0 on success, error code on failure
 * @see ms_status_codes.h
 */
int	signals_restore(void);

#endif