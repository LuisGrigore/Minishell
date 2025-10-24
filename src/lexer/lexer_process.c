/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:00:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/24 07:14:31 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static int parse_word_and_get(t_lstate *ls, char **out_word)
{
    int pr;

    *out_word = NULL;
    pr = parse_word(ls->line, ls->i, ls->len, out_word);
    if (pr == -1)
        return LEXER_ERR;
    if (pr == -2)
        return LEXER_SYNTAX_ERR;
    return MS_OK;
}

t_token_type determine_type_and_clear(t_lstate *ls)
{
    if (*(ls->next_is_redir_arg))
    {
        *(ls->next_is_redir_arg) = false;
        return TOKEN_ARG;
    }
    if (*(ls->expect_cmd))
    {
        *(ls->expect_cmd) = false;
        return TOKEN_CMD;
    }
    return TOKEN_ARG;
}

static void create_and_push_token(t_gen_list *list, t_token_type type, char *word)
{
    t_token *tok;

    tok = create_token(type, word);
    gen_list_push_back(list, tok);
}

int parse_word_and_push(t_lstate *ls)
{
    char *word;
    int r;
    t_token_type type;

    word = NULL;
    r = parse_word_and_get(ls, &word);
    if (r != MS_OK)
        return r;
    type = determine_type_and_clear(ls);
    create_and_push_token(ls->tokens_list, type, word);
    return MS_OK;
}

int process_next_token(t_lstate *ls)
{
    int r;

    *(ls->i) = skip_spaces(ls->line, *(ls->i), ls->len);
    if (*(ls->i) >= ls->len)
        return MS_OK;
    r = push_two_char_op(ls->line, ls->i, ls->tokens_list, ls->next_is_redir_arg);
    if (r < 0)
        return LEXER_ERR;
    if (r == 1)
        return MS_OK;
    r = push_one_char_op(ls->line, ls->i, ls->tokens_list,
        ls->next_is_redir_arg, ls->expect_cmd);
    if (r < 0)
        return LEXER_ERR;
    if (r == 1)
        return MS_OK;
    return parse_word_and_push(ls);
}