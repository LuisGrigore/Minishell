/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:00:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/24 07:14:31 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

int build_out_word(t_pstate *st, size_t start, char **out_word)
{
    size_t wlen;
    size_t k;

    if (*(st->blen) == 0)
    {
        wlen = *(st->i) - start;
        *out_word = ft_strndup(st->line + start, wlen);
        if (!*out_word)
            return -1;
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