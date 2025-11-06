/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:09:07 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/06 23:55:25 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

// static int skip_and_check_eof(t_lstate *ls)
// {
// 	*(ls->i) = skip_spaces(ls->line, *(ls->i), ls->len);
// 	if (*(ls->i) >= ls->len)
// 		return MS_OK;
// 	return 1;
// }

// static int try_two_char_ops(t_lstate *ls)
// {
// 	int r;

// 	r = push_two_char_op(ls->line, ls->i, ls->tokens_list, ls->next_is_redir_arg);
// 	if (r < 0)
// 		return LEXER_ERR;
// 	if (r == 1)
// 		return MS_OK;
// 	return 1;
// }

// static int try_one_char_ops(t_lstate *ls)
// {
// 	int r;

// 	r = push_one_char_op(ls->line, ls->i, ls->tokens_list, ls->next_is_redir_arg, ls->expect_cmd);
// 	if (r < 0)
// 		return LEXER_ERR;
// 	if (r == 1)
// 		return MS_OK;
// 	return 1;
// }


int lexer_tokenize(const char *line, t_gen_list *tokens_list, t_gen_list *env)
{
	size_t i;
	t_lstate ls;
	int r;
	i = 0;
	r = lexer_init_state(line, tokens_list, &i, &ls, env);
	if (r != MS_OK)
		return r;
	return run_token_loop(&ls);
}
 int lexer_init_state(const char *line, t_gen_list *tokens_list,
	size_t *i, t_lstate *ls, t_gen_list *env)
{
	if (!tokens_list)
		return LEXER_NULL_ERR;
	*i = 0;
	ls->line = line;
	ls->i = i;
	ls->len = ft_strlen(line);
	ls->tokens_list = tokens_list;
	ls->env = env;
	ls->expect_cmd_val = true;
	ls->next_is_redir_arg_val = false;
	ls->next_is_redir_arg = &ls->next_is_redir_arg_val;
	ls->expect_cmd = &ls->expect_cmd_val;
	return MS_OK;
}

int run_token_loop(t_lstate *ls)
{
	int r;
	size_t prev_i;

	while (*(ls->i) < ls->len)
	{
		prev_i = *(ls->i);
		r = process_next_token(ls);
		if (r == LEXER_SYNTAX_ERR)
			return LEXER_SYNTAX_ERR;
		if (r == LEXER_ERR)
		{
			if (ls->tokens_list)
				gen_list_destroy(ls->tokens_list, free);
			return LEXER_ERR;
		}

		if (*(ls->i) == prev_i)
		{
			/* No progress: advance by one to avoid hang (safety). */
			(*(ls->i))++;
		}
	}
	return MS_OK;
}


