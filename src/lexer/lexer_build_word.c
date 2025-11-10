/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:54:04 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/10 20:01:40 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static int	process_unquoted_chunk(t_environment *env, char *p, size_t *i,
		char **buf)
{
	size_t	start;
	char	*seg;
	int		status;

	start = *i;
	while (p[*i] && !is_space(p[*i]) && !is_operator_char(p[*i])
		&& p[*i] != '\'' && p[*i] != '"' && p[*i] != '$')
		*i = *i + 1;
	if (*i > start)
	{
		seg = ft_strndup(&p[start], *i - start);
		if (!seg)
			return (MS_ALLOCATION_ERR);
		*buf = append_segment(*buf, seg);
		if (!*buf)
			return (MS_ALLOCATION_ERR);
	}
	if (p[*i] == '$')
	{
		*i = *i + 1;
		status = expand_variable(env, p, i, buf);
		return (status);
	}
	return (MS_OK);
}

static int	process_double_quoted_chunk(t_environment *env, char *p, size_t *i,
		char **buf)
{
	size_t	start;
	char	*seg;
	int		status;

	*i = *i + 1;
	start = *i;
	while (p[*i] && p[*i] != '"')
	{
		if (p[*i] == '$')
		{
			if (*i > start)
			{
				seg = ft_strndup(&p[start], *i - start);
				if (!seg)
					return (MS_ALLOCATION_ERR);
				*buf = append_segment(*buf, seg);
				if (!*buf)
					return (MS_ALLOCATION_ERR);
			}
			*i = *i + 1;
			status = expand_variable(env, p, i, buf);
			if (status != MS_OK)
				return (status);
			start = *i;
			continue ;
		}
		*i = *i + 1;
	}
	if (!p[*i])
		return (LEXER_UNCLOSED_QUOTE_ERR);
	if (*i > start)
	{
		seg = ft_strndup(&p[start], *i - start);
		if (!seg)
			return (MS_ALLOCATION_ERR);
		*buf = append_segment(*buf, seg);
		if (!*buf)
			return (MS_ALLOCATION_ERR);
	}
	*i = *i + 1;
	return (MS_OK);
}

static int	handle_single_quoted_segment(char *p, size_t *i, char **buf)
{
	size_t	start;
	char	*seg;

	*i = *i + 1;
	start = *i;
	while (p[*i] && p[*i] != '\'')
		*i = *i + 1;
	if (!p[*i])
		return (LEXER_UNCLOSED_QUOTE_ERR);
	seg = ft_strndup(&p[start], *i - start);
	if (!seg)
		return (MS_ALLOCATION_ERR);
	*buf = append_segment(*buf, seg);
	if (!*buf)
		return (MS_ALLOCATION_ERR);
	*i = *i + 1;
	return (MS_OK);
}

int	build_word(t_environment *env, char *p, size_t *i, char **buf)
{
	int	status;

	while (p[*i] && !is_space(p[*i]) && !is_operator_char(p[*i]))
	{
		if (p[*i] == '\'')
		{
			status = handle_single_quoted_segment(p, i, buf);
			if (status != MS_OK)
				return (status);
		}
		else if (p[*i] == '"')
		{
			status = process_double_quoted_chunk(env, p, i, buf);
			if (status != MS_OK)
				return (status);
		}
		else
		{
			status = process_unquoted_chunk(env, p, i, buf);
			if (status != MS_OK)
				return (status);
		}
	}
	return (MS_OK);
}
