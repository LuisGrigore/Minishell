/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 05:38:09 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/12 16:22:02 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../external/gen_list/gen_list.h"
# include "ms_status_codes.h"

/**
 * Tokenize and parse a single command-line string into a list of commands.
 *
 * This function performs tokenization of the input `line` and converts the
 * resulting tokens into `t_command` objects which are appended to the
 * provided `commands` list. The `commands` list must be created by the caller
 * (for example via `gen_list_create`) and will be populated on success.
 *
 * The function returns a status code defined in `ms_status_codes.h`:
 *  - MS_OK on success (commands appended to `commands`).
 *  - PARSER_ERR or other error codes on failure.
 *
 * @param line Null-terminated input string to parse.
 * @param commands Output list where parsed t_command* objects will be appended.
 * @return MS_OK on success, or an error status otherwise.
 */
/*
 * parse_line now also receives the environment list so lexer can expand
 * variables according to quoting rules during tokenization.
 */
int	parse_line(char *line, t_gen_list *commands, t_environment *env);

#endif