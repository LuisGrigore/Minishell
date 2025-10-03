/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:41:17 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/03 19:06:25 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../external/gen_list/gen_list.h"
#include <stdbool.h>

typedef enum e_token_type
{
	TOKEN_CMD,
	TOKEN_ARG,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}					t_token_type;

typedef struct s_token t_token;

t_gen_list			*lexer_tokenize(const char *line);
void 				lexer_destroy(t_gen_list *tokens);

t_token_type lexer_get_token_type(t_token * token);
char *lexer_get_token_content(t_token * token);

bool lexer_is_token_type(t_token * token, t_token_type type);

// DEBUG

void	print_tokens(t_gen_list *tokens);

#endif