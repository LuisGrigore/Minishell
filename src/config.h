/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:10:01 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/07 21:01:07 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/* ============================================================
**  PATHS
** ============================================================
*/
#define PATH_HEREDOC_TEMP_FILE "./minishell_heredoc.temp"

/* ============================================================
**  STATUS_CODES
** ============================================================
*/
#define SYSTEM_STATUS_BEGIN 0
#define COMMAND_STATUS_BEGIN 100
#define ENVIRONMENT_STATUS_BEGIN 200
#define EXECUTER_STATUS_BEGIN 300
#define HISTORY_MANAGER_STATUS_BEGIN 400
#define LEXER_STATUS_BEGIN 500
#define PARSER_STATUS_BEGIN 600
#define REDIRECT_MANAGER_STATUS_BEGIN 800
#define SIGNAL_MANAGER_STATUS_BEGIN 900

#endif