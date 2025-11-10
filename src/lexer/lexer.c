/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:24:35 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/10 19:50:15 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

int	tokenize_line_aux(char *current_char, t_gen_list *tokens, char *line,
		t_environment *env)
{
	int	status_code;

	if (!current_char || !tokens || !line)
		return (LEXER_NULL_ERR);
	while (*current_char && is_space(*current_char))
		current_char++;
	if (*current_char == '\0')
		return (MS_OK);
	if (is_word_start_char(*current_char))
		status_code = add_word_token(&current_char, tokens, env);
	else if (is_operator_char(*current_char))
		status_code = add_operator_token(&current_char, tokens, current_char);
	else
		return (LEXER_UNSUPORTED_CHARACTER_ERR);
	if (status_code != MS_OK)
		return (status_code);
	return (tokenize_line_aux(current_char, tokens, line, env));
}

int	tokenize_line(char *line, t_gen_list *tokens, t_environment *env)
{
	return (tokenize_line_aux(line, tokens, line, env));
}
