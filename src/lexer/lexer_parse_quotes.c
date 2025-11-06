/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:00:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/06 23:34:29 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

int parse_single_quote(t_pstate *st)
{
    (*(st->i))++;
    while (*(st->i) < st->len && st->line[*(st->i)] != '\'')
    {
        if (append_char(st, st->line[*(st->i)]) < 0)
            return -1;
        (*(st->i))++;
    }
    if (*(st->i) >= st->len || st->line[*(st->i)] != '\'')
        return -2;
    (*(st->i))++;
    return 1;
}

int parse_double_quote(t_pstate *st)
{
    (*(st->i))++;
    while (*(st->i) < st->len && st->line[*(st->i)] != '"')
    {
        if (st->line[*(st->i)] == '\\' && *(st->i) + 1 < st->len)
        {
            if (append_char(st, st->line[*(st->i) + 1]) < 0)
                return -1;
            *(st->i) += 2;
        }
        else
        {
            if (append_char(st, st->line[*(st->i)]) < 0)
                return -1;
            (*(st->i))++;
        }
    }
    if (*(st->i) >= st->len || st->line[*(st->i)] != '"')
        return -2;
    (*(st->i))++;
    return 1;
}

int parse_backslash_escape(t_pstate *st)
{
    if (*(st->i) + 1 >= st->len)
        return 0;
    if (append_char(st, st->line[*(st->i) + 1]) < 0)
        return -1;
    *(st->i) += 2;
    return 1;
}

int handle_loop_char(t_pstate *st)
{
    char c;
    int r;

    c = st->line[*(st->i)];
    if (c == '\'')
    {
        r = parse_single_quote(st);
        if (r != 1)
            return r;
        return 1;
    }
    if (c == '"')
    {
        r = parse_double_quote(st);
        if (r != 1)
            return r;
        return 1;
    }
    if (c == '\\' && *(st->i) + 1 < st->len)
    {
        r = parse_backslash_escape(st);
        if (r < 0)
            return -1;
        return 1;
    }
    if (append_char(st, c) < 0)
        return -1;
    /* fix parentheses: check previous-previous char for operator and current is not space */
    if (*(st->i) >= 2 && is_operator_char(st->line[*(st->i) - 2]) && !is_space(st->line[*(st->i)]))
        return 0;
    (*(st->i))++;
    return 1;
}

int parse_word_loop(t_pstate *st)
{
    int r;

    while (*(st->i) < st->len && !is_space(st->line[*(st->i)])
        && !is_operator_char(st->line[*(st->i)]))
    {
        r = handle_loop_char(st);
        if (r != 1)
            return r;
        
    }
    return 1;
}