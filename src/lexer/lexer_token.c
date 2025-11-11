/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:42:20 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/11 16:13:03 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

t_token_type	lexer_get_token_type(t_token *token)
{
	return (token->type);
}

char	*lexer_get_token_content(t_token *token)
{
	if (!token || !token->value)
		return (NULL);
	return (token->value);
}

bool	lexer_is_token_type(t_token *token, t_token_type type)
{
	if (!token)
		return (false);
	return (lexer_get_token_type(token) == type);
}
