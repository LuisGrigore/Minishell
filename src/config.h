/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:10:01 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/12 16:40:29 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/* ============================================================
**  PATHS
** ============================================================
*/
# define PATH_HEREDOC_TEMP_FILE "./minishell_heredoc.temp"

/* ============================================================
**  STATUS_CODES
** ============================================================
*/
# define SYSTEM_STATUS_BEGIN 0
# define SYSTEM_STATUS_END 99

# define COMMAND_STATUS_BEGIN 100
# define COMMAND_STATUS_END 199

# define EXECUTER_STATUS_BEGIN 300
# define EXECUTER_STATUS_END 399

# define LEXER_STATUS_BEGIN 500
# define LEXER_STATUS_END 599

# define PARSER_STATUS_BEGIN 600
# define PARSER_STATUS_END 699

# define REDIRECT_MANAGER_STATUS_BEGIN 700
# define REDIRECT_MANAGER_STATUS_END 799

# define PIPE_MANAGER_STATUS_BEGIN 800
# define PIPE_MANAGER_STATUS_END 899

# define EXTERNALY_DEFINED_STATUS_BEGIN 1000

#endif