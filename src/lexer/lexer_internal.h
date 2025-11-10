/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:45:17 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/10 19:59:19 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "../external/libft/libft.h"
# include "../include/lexer.h"
# include <stdlib.h>

struct				s_token
{
	t_token_type	type;
	char			*value;
};

t_token				*create_token(t_token_type type, char *value);
void				destroy_token(t_token *token);
char				*ft_strndup(const char *s, size_t n);
int					is_space(char c);
int					is_operator_char(char c);
t_token_type		operator_type(const char *op, size_t len);
bool				is_word_start_char(char c);

int					add_operator_token(char **current_char, t_gen_list *tokens,
						char *line);
int					add_word_token(char **current_char, t_gen_list *tokens,
						t_environment *env);
int					build_word(t_environment *env, char *p, size_t *i,
						char **buf);
char				*append_segment(char *buf, char *seg);
char				*append_literal_char(char *buf, char c);
int					expand_variable(t_environment *env, char *p, size_t *i,
						char **buf);

#endif