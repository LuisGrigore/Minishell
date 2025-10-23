/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:45:17 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/23 16:31:35 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_INTERNAL_H
#define TOKENIZER_INTERNAL_H

#include "../include/lexer.h"
#include "../external/libft/libft.h"
#include <stdlib.h>


struct s_token
{
	t_token_type	type;
	char			*value;
};
typedef struct s_pstate 
{
	const char *line;
	size_t *i;
	size_t len;
	char **buf;
	size_t *bcap;
	size_t *blen;
} t_pstate;

typedef struct s_lstate 
{
	const char *line;
	size_t *i;
	size_t len;
	t_gen_list *tokens_list;
	bool next_is_redir_arg_val;
	bool expect_cmd_val;
	bool *next_is_redir_arg;
	bool *expect_cmd;
} t_lstate;

t_token *create_token(t_token_type type, char *value);
void destroy_token(t_token *token);
char *ft_strndup(const char *s, size_t n);
int is_space(char c);
int is_operator_char(char c);
int match_two_char_op(const char *s, size_t pos, const char *op);
t_token_type operator_type(const char *op, size_t len);

#endif