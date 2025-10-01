/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:45:17 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/01 14:54:39 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_INTERNAL_H
#define TOKENIZER_INTERNAL_H

#include "../include/tokenizer.h"
# include "../external/gen_list/gen_list.h"
#include "../external/libft/libft.h"
#include <stdlib.h>


t_token *create_token(t_token_type type, char *value);
void destroy_token(t_token *token);
char *ft_strndup(const char *s, size_t n);
int is_space(char c);
int is_operator_char(char c);
int match_two_char_op(const char *s, size_t pos, const char *op);
t_token_type operator_type(const char *op, size_t len);

#endif