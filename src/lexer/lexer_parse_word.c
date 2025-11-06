/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:00:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/06 23:34:28 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

int build_out_word(t_pstate *st, size_t start, char **out_word)
{
    size_t wlen;
    size_t k;
    if (*(st->blen) == 0)
    {
        /* No chars were appended to the temporary buffer. That can happen when
         * the token is composed only of quotes (e.g. '' or ""). In that case
         * we must return the interpreted value (empty string) instead of the
         * raw substring which would include the quotes. For safety, strip any
         * single or double quote characters from the raw range and return the
         * resulting string. */
        size_t i;
        size_t cnt = 0;

        /* count non-quote characters between start and current index */
        for (i = start; i < *(st->i); ++i)
        {
            if (st->line[i] != '\'' && st->line[i] != '"')
                cnt++;
        }
        *out_word = malloc(cnt + 1);
        if (!*out_word)
            return -1;
        k = 0;
        for (i = start; i < *(st->i); ++i)
        {
            if (st->line[i] != '\'' && st->line[i] != '"')
                (*out_word)[k++] = st->line[i];
        }
        (*out_word)[k] = '\0';
    }
    else
    {
        *out_word = malloc(*(st->blen) + 1);
        if (!*out_word)
            return -1;
        k = 0;
        while (k < *(st->blen))
        {
            (*out_word)[k] = (*(st->buf))[k];
            k++;
        }
        (*out_word)[*(st->blen)] = '\0';
        free(*(st->buf));
    }
    return 1;
}

int finalize_parse_word(t_pstate *st, char *buf, size_t start, char **out_word)
{
    int r;

    r = build_out_word(st, start, out_word);
    if (r != 1)
    {
        free(buf);
        return -1;
    }
    return 1;
}

int parse_word(const char *line, size_t *i, size_t len, char **out_word)
{
    size_t start;
    char *buf;
    size_t bcap;
    size_t blen;
    t_pstate st;
    int r;

    start = *i;
    buf = NULL;
    bcap = 0;
    blen = 0;
    pstate_init(&st, line, i, len, &buf, &bcap, &blen);
    r = parse_word_loop(&st);
    if (r != 1)
    {
        free(buf);
        return r;
    }
    return finalize_parse_word(&st, buf, start, out_word);
}