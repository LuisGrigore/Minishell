/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:10:01 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/06 13:50:20 by lgrigore         ###   ########.fr       */
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


#define EXECUTER_ERROR_BEGIN 300
#define HISTORY_MANAGER_ERROR_BEGIN 400
#define LEXER_ERROR_BEGIN 500
#define PARSER_ERROR_BEGIN 600
#define REDIRECT_MANAGER_ERROR_BEGIN 800
#define SIGNAL_MANAGER_ERROR_BEGIN 900

#endif