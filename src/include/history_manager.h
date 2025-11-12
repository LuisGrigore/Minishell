/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 05:02:57 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/12 05:02:58 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_MANAGER_H
# define HISTORY_MANAGER_H

# include <stdbool.h>

/**
 * @brief Adds a valid command line to the shell history
 *
 * Validates and stores command lines in the shell history for later recall.
 * Performs the following validations before storing:
 *   - Rejects empty or whitespace-only commands
 *   - Rejects lines starting/ending with pipe operator
 *   - Rejects commands with unclosed quotes
 *   - Removes duplicate consecutive entries
 *
 * @param line The command line to store in history
 * @return true if stored successfully, false if rejected
 *
 * @see history_clean
 */
bool	history_add(char *line);

/**
 * @brief Cleans up the history manager resources
 *
 * Frees all allocated memory associated with the command history
 * and resets the history state. Should be called before the shell exits.
 */
void	history_clean(void);

#endif