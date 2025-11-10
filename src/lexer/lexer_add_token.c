/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_add_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:48:26 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/10 19:59:52 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

int	add_operator_token(char **current_char, t_gen_list *tokens, char *line)
{
	size_t	start;
	size_t	end;
	char	*value;
	t_token	*token;

	start = 0;
	end = start;
	while (is_operator_char(line[end]))
		end++;
	value = ft_strndup(&line[start], end - start);
	if (!value)
		return (MS_ALLOCATION_ERR);
	token = create_token(operator_type(value, end - start), value);
	if (!token)
		return (free(value), MS_ALLOCATION_ERR);
	gen_list_push_back(tokens, token);
	*current_char += (end - start);
	return (MS_OK);
}

int	add_word_token(char **current_char, t_gen_list *tokens, t_environment *env)
{
	char	*p;
	char	*buf;
	size_t	i;
	int		status;
	t_token	*token;

	if (!current_char || !*current_char || !tokens)
		return (LEXER_NULL_ERR);
	p = *current_char;
	i = 0;
	buf = ft_strdup("");
	if (!buf)
		return (MS_ALLOCATION_ERR);
	status = build_word(env, p, &i, &buf);
	if (status != MS_OK)
	{
		free(buf);
		return (status);
	}
	*current_char = p + i;
	if (*buf == '\0')
	{
		free(buf);
		return (MS_OK);
	}
	token = create_token(TOKEN_WORD, buf);
	if (!token)
	{
		free(buf);
		return (MS_ALLOCATION_ERR);
	}
	gen_list_push_back(tokens, token);
	return (MS_OK);
}
