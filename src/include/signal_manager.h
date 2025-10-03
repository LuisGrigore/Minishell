/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:06:18 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/03 15:09:13 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MANAGER_H
#define SIGNAL_MANAGER_H


/**
 * @brief Configures signals for the shell's interactive mode.
 * 
 * This function is used when the shell is waiting for user input.
 * Typically, it ignores SIGQUIT and handles SIGINT to interrupt the
 * current line without exiting the shell.
 */
void signals_init_interactive(void);

/**
 * @brief Configures signals for command execution.
 * 
 * This function is used before executing an external command. It allows
 * the child process to receive signals like SIGINT and SIGQUIT normally,
 * while the parent shell can handle them appropriately.
 */
void signals_init_execution(void);

/**
 * @brief Configures signals for heredoc mode.
 * 
 * This function is used when reading a heredoc. It typically handles
 * SIGINT to cancel the heredoc input without affecting the main shell.
 */
void signals_init_heredoc(void);

/**
 * @brief Restores the original signal configuration.
 * 
 * This function is used to return the shell to its default signal
 * behavior after having changed the configuration for execution,
 * heredoc, or interactive mode.
 */
void signals_restore(void);

#endif