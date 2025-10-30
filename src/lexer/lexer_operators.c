/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:00:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/27 18:04:39 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void create_and_push_token(t_gen_list *list, t_token_type type, char *word)
{
    t_token *tok;

    tok = create_token(type, word);
    gen_list_push_back(list, tok);
}

int push_two_char_op(const char *line, size_t *i,
    t_gen_list *tokens_list, bool *next_is_redir_arg)
{
    char *op;
    t_token *tok;

    if (!match_two_char_op(line, *i, ">>") && !match_two_char_op(line, *i, "<<"))
        return 0;
    op = ft_strndup(line + *i, 2);
    if (!op)
        return -1;
    tok = create_token(operator_type(op, 2), op);
    gen_list_push_back(tokens_list, tok);
    *i += 2;
    if (tok->type == TOKEN_REDIR_APPEND || tok->type == TOKEN_HEREDOC)
        *next_is_redir_arg = true;
    return 1;
}

int push_one_char_op(const char *line, size_t *i,
    t_gen_list *tokens_list, bool *next_is_redir_arg, bool *expect_cmd)
{
    char *op;
    t_token *tok;

    if (!is_operator_char(line[*i]))
        return 0;
    op = ft_strndup(line + *i, 1);
    if (!op)
        return -1;
    tok = create_token(operator_type(op, 1), op);
    gen_list_push_back(tokens_list, tok);
    (*i)++;
    if (tok->type == TOKEN_REDIR_IN || tok->type == TOKEN_REDIR_OUT)
        *next_is_redir_arg = true;
    else if (tok->type == TOKEN_PIPE)
        *expect_cmd = true;
    return 1;
}