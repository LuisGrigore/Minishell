/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:07:05 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/19 20:10:29 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "../external/libft/libft.h"
# include "../include/command.h"
# include "../include/lexer.h"
# include "../include/parser.h"
# include <stdlib.h>

/**
 * @brief Create or update a command object from a TOKEN_CMD token.
 *
 * If `current_cmd` is NULL a new t_command is allocated and initialized
 * with the token content as the command name. Otherwise the function will
 * add the token content as an argument to the existing command.
 *
 * @param tok Token representing the command (TOKEN_CMD).
 * @param current_cmd Existing command being built or NULL to create a new one.
 * @return Pointer to the updated or newly created t_command, or NULL on
 *         allocation failure.
 */
t_command	*handle_command_token(t_token *tok, t_command *current_cmd);

/**
 * @brief Create or update a command object from a TOKEN_ARG token.
 *
 * Ensures a command object exists (creates an empty one if necessary) and
 * appends the token content as an argument.
 *
 * @param tok Token representing the argument (TOKEN_ARG).
 * @param current_cmd Existing command being built or NULL to create a new one.
 * @return Pointer to the updated or newly created t_command, or NULL on
 *         allocation failure.
 */
t_command	*handle_arg_token(t_token *tok, t_command *current_cmd);

/**
 * @brief Handle a redirection token and attach the redirection to the
 *        current command object.
 *
 * Reads the next token (if present) as the redirection target. If the
 * current command has no name yet, consumes an additional token to use as
 * the command name. Supported redirect tokens: <, >, >>, << (heredoc).
 *
 * @param tok Token representing the redirection operator.

 * @param file_tok Optional token representing the redirection target
 * (may be NULL).
 * @param current_cmd Command object to attach the redirection to; if NULL a
 *        new command will be created.
 * @param it Iterator used to consume extra tokens when needed.
 * @return Pointer to the updated or newly created t_command, or NULL on error.
 */
t_command	*handle_redirect(t_token *tok, t_token *file_tok,
				t_command *current_cmd, t_gen_list_iter *it);

/**
 * @brief Finalize the current command on a pipe token.
 *
 * Pushes the provided `current_cmd` into the `commands` list. This is called
 * when a pipe token is encountered to close the current command and prepare
 * for the next one.
 *
 * @param current_cmd Command being finalized (may not be NULL).
 * @param commands List where the finalized command will be appended.
 * @return 1 on success, 0 if `current_cmd` was NULL (invalid pipe usage).
 */
int			handle_pipe_token(t_command *current_cmd, t_gen_list *commands);

// DEBUG
void		print_commands(t_gen_list *commands);

#endif
