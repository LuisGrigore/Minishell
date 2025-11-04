/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_status_codes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:19:01 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/30 18:28:59 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERRORS_H
#define MS_ERRORS_H

#include "../config.h"

typedef enum e_ms_status_code
{
	//System
	MS_OK = SYSTEM_STATUS_BEGIN,
	MS_FORK_ERR,
	MS_PIPE_ERR,
	MS_DUP2_ERR,
	MS_ALLOCATION_ERR,
	MS_CLOSE_ERR,
	MS_SIGNAL_ERR,
	MS_FILE_ERR,
	//Command
	COMMAND_ERR = COMMAND_STATUS_BEGIN,
	COMMAND_MALFORMED_ERR,
	COMMAND_NOT_FOUND_ERR,
	COMMAND_PERMISSION_ERR,
	COMMAND_IS_DIR_ERR,
	BINBUILTIN_ERR = BINBUILTIN_STATUS_BEGIN,
	BINBUILTIN_NOT_FOUND_ERR,
	BINBUILTIN_PERMISSION_ERR,
	
	
	//Environment
	ENVIRONMENT_ERR = ENVIRONMENT_STATUS_BEGIN,
	//Executer
	EXECUTER_ERR = EXECUTER_STATUS_BEGIN,
	//Lexer
	LEXER_ERR = LEXER_STATUS_BEGIN,
	LEXER_NULL_ERR,
	LEXER_SYNTAX_ERR,
	//Parser
	PARSER_ERR = PARSER_STATUS_BEGIN,
	PARSER_NULL_ERR,
	//Redirect Manager
	REDIRECT_MANAGER_ERR = REDIRECT_MANAGER_STATUS_BEGIN,
	REDIRECT_MANAGER_ERR_INVALID_FD,
	REDIRECT_MANAGER_ERR_SYNTAX,
	
} t_ms_status_code;

#endif