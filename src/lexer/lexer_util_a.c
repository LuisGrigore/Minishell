/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:38:09 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/11 15:02:29 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*p;
	size_t	i;

	p = NULL;
	p = malloc(n + 1);
	i = 0;
	if (!p)
		return (NULL);
	while (i < n && s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_operator_char(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	return (0);
}

t_token_type	operator_type(const char *op, size_t len)
{
	if (len == 1)
	{
		if (op[0] == '|')
			return (TOKEN_PIPE);
		if (op[0] == '<')
			return (TOKEN_REDIR_IN);
		if (op[0] == '>')
			return (TOKEN_REDIR_OUT);
	}
	else if (len == 2)
	{
		if (op[0] == '<' && op[1] == '<')
			return (TOKEN_HEREDOC);
		if (op[0] == '>' && op[1] == '>')
			return (TOKEN_REDIR_APPEND);
	}
	return (TOKEN_ARG);
}

bool	is_word_start_char(char c)
{
	return (!is_space(c) && !is_operator_char(c) && c != '\0' && !is_unsuported_char(c));
}
