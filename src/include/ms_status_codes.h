/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_status_codes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:19:01 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/06 23:43:03 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERRORS_H
#define MS_ERRORS_H

#include "../config.h"

typedef enum e_ms_status_code
{
	//System
	MS_OK = SYSTEM_STATUS_BEGIN,
	MS_ERR_FORK,
	MS_ERR_PIPE,
	MS_DUP2_ERR,
	MS_MALLOC_ERR,
	MS_CLOSE_ERR,
	MS_SIGNAL_ERR,
	MS_ERR_FILE,
	//Command
	COMMAND_ERROR = COMMAND_STATUS_BEGIN,
	COMMAND_MALFORMED,
	//Environment
	ENVIRONMENT_ERROR = ENVIRONMENT_STATUS_BEGIN,
	//Executer
	EXECUTER_ERROR = EXECUTER_STATUS_BEGIN,
	//Lexer
	LEXER_ERROR = LEXER_STATUS_BEGIN,
	LEXER_ERR_NULL,
	LEXER_ERR_SYNTAX,
	//Parser
	PARSER_ERROR = PARSER_STATUS_BEGIN,
	PARSER_NULL_ERR,
} t_ms_status_code;

#endif