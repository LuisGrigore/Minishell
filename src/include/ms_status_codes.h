/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_status_codes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:19:01 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/12 05:02:46 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STATUS_CODES_H
# define MS_STATUS_CODES_H

# include "../config.h"

typedef enum e_ms_status_code
{
	// System
	MS_OK = SYSTEM_STATUS_BEGIN,
	MS_FORK_ERR,
	MS_PIPE_ERR,
	MS_DUP2_ERR,
	MS_ALLOCATION_ERR,
	MS_CLOSE_ERR,
	MS_SIGNAL_ERR,
	MS_OPEN_ERR,
	MS_PATH_ERR,
	// Command
	COMMAND_SUCCESS = COMMAND_STATUS_BEGIN,
	COMMAND_ERR,
	COMMAND_MALFORMED_ERR,
	COMMAND_NOT_FOUND_ERR,
	COMMAND_PERMISSION_ERR,
	COMMAND_IS_DIR_ERR,
	COMMAND_MISSING_ARGS_ERR,
	COMMAND_TOO_MANY_ARGS_ERR,
	COMMAND_INVALID_ARGS_ERR,
	COMMAND_NUMERIC_ARG_REQUIRED_ERR,
	COMMAND_NO_SUCH_FILE_OR_DIR_ERR,
	// Executer
	EXECUTER_ERR = EXECUTER_STATUS_BEGIN,
	// Lexer
	LEXER_ERR = LEXER_STATUS_BEGIN,
	LEXER_NULL_ERR,
	LEXER_SYNTAX_ERR,
	LEXER_UNSUPORTED_CHARACTER_ERR,
	LEXER_UNCLOSED_QUOTE_ERR,
	// Parser
	PARSER_ERR = PARSER_STATUS_BEGIN,
	PARSER_NULL_ERR,
	PARSER_SYNTAX_ERR,
	// Redirect
	REDIRECT_MALFORMED_ERR = REDIRECT_MANAGER_STATUS_BEGIN,
	REDIRECT_NO_HEADERDOC_DELIMITER_ERR,
	// Pipe
	PIPE_MANAGER_IS_NULL = PIPE_MANAGER_STATUS_BEGIN,
	PIPE_MANAGER_MALFORMED,
	// Exit
	EXTERNALY_DEFINED_STATUS_CODE = EXTERNALY_DEFINED_STATUS_BEGIN,
}	t_ms_status_code;

#endif