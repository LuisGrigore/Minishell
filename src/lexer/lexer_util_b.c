/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:56:55 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/11 15:01:33 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

bool is_unsuported_char(char c)
{
	if (c == '\\' || c == ';')
		return true;
	return false;
}

char	*append_segment(char *buf, char *seg)
{
	char	*tmp;

	if (!seg)
		return (buf);
	tmp = ft_strjoin(buf, seg);
	free(buf);
	free(seg);
	return (tmp);
}

char	*append_literal_char(char *buf, char c)
{
	char	s[2];

	s[0] = c;
	s[1] = '\0';
	return (append_segment(buf, ft_strdup(s)));
}

int	expand_variable(t_environment *env, char *p, size_t *i, char **buf)
{
	char	name[256];
	size_t	j;
	char	*var;

	j = 0;
	if (p[*i] == '?')
	{
		var = env_get(env, "?");
		*i = *i + 1;
		if (var)
		{
			*buf = append_segment(*buf, var);
			if (!*buf)
				return (MS_ALLOCATION_ERR);
		}
		return (MS_OK);
	}
	while (p[*i] && (ft_isalnum(p[*i]) || p[*i] == '_') && j + 1 < sizeof(name))
	{
		name[j] = p[*i];
		j = j + 1;
		*i = *i + 1;
	}
	name[j] = '\0';
	if (j == 0)
	{
		*buf = append_literal_char(*buf, '$');
		return (*buf ? MS_OK : MS_ALLOCATION_ERR);
	}
	var = env_get(env, name);
	if (var)
	{
		*buf = append_segment(*buf, var);
		if (!*buf)
			return (MS_ALLOCATION_ERR);
	}
	return (MS_OK);
}
