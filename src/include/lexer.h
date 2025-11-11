/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:41:17 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/11 16:39:43 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../external/gen_list/gen_list.h"
# include "environment.h"
# include "ms_status_codes.h"
# include <stdbool.h>

/**
 * Enumeration of all possible token types recognized by the lexer.
 *
 * TOKEN_CMD        : A command name (e.g., "ls", "echo").
 * TOKEN_ARG        : A command argument.
 * TOKEN_PIPE       : The pipe operator '|'.
 * TOKEN_REDIR_IN   : Input redirection '<'.
 * TOKEN_REDIR_OUT  : Output redirection '>'.
 * TOKEN_REDIR_APPEND: Output append redirection '>>'.
 * TOKEN_HEREDOC    : Heredoc redirection '<<'.
 */
typedef enum e_token_type
{
	TOKEN_WORD,
	// TOKEN_CMD,
	// TOKEN_ARG,
	INVALID_OPERATOR,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}						t_token_type;

/**
 * Opaque token structure representing a single lexical element
 * in the parsed command line.
 */
typedef struct s_token	t_token;

/* ============================================================
**  Lexer Lifecycle
** ============================================================
*/

/**
 * Splits a raw command line into a list of tokens.
 *
 * @param line A null-terminated string containing the input command line.
 *
 * @return A pointer to a t_gen_list containing t_token* elements,
 *         or NULL if tokenization fails.
 *
 * Each token corresponds to a command, argument, or operator,
 * as defined in t_token_type.
 */
/*
 * Tokenize the input line. The lexer now needs access to the environment
 * so it can expand variables according to quoting rules (single vs double
 * quotes). Pass the environment list; it may be NULL if not available.
 */
int						tokenize_line(char *line, t_gen_list *tokens,
							t_environment *env);

/**
 * Frees all memory associated with a token list.
 *
 * @param tokens The token list returned by lexer_tokenize().
 */
void					lexer_destroy(t_gen_list *tokens);

/* ============================================================
**  Lexer Token
** ============================================================
*/

/**
 * Retrieves the type of a given token.
 *
 * @param token A pointer to the token.
 *
 * @return The token's type (see t_token_type).
 */
t_token_type			lexer_get_token_type(t_token *token);

/**
 * Retrieves the string content of a given token.
 *
 * @param token A pointer to the token.
 *
 * @return A pointer to the token's content string.
 *         The string is owned by the token and must not be freed directly.
 */
char					*lexer_get_token_content(t_token *token);

/**
 * Checks if a token matches a given type.
 *
 * @param token A pointer to the token.
 * @param type  The token type to check against.
 *
 * @return true if the token's type matches the given type,
 *         false otherwise.
 */
bool					lexer_is_token_type(t_token *token, t_token_type type);

/* ============================================================
**  Debug
** ============================================================
*/

void					print_tokens(t_gen_list *tokens);

#endif