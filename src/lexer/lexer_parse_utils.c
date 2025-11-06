/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:00:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/06 23:51:10 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void pstate_init(t_pstate *st, const char *line, size_t *i, size_t len,
    char **buf, size_t *bcap, size_t *blen, t_gen_list *env)
{
    st->line = line;
    st->i = i;
    st->len = len;
    st->buf = buf;
    st->bcap = bcap;
    st->blen = blen;
    st->env = env;
}

int ensure_capacity(t_pstate *st, size_t need)
{
    size_t nc;
    char *tmp;

    if (*(st->bcap) >= need)
        return 0;
    if (*(st->bcap))
        nc = *(st->bcap) * 2;
    else
        nc = 64;
    while (nc <= need)
        nc *= 2;
    tmp = malloc(nc);
    if (!tmp)
        return -1;
    if (*(st->buf))
    {
        ft_memcpy(tmp, *(st->buf), *(st->blen));
        free(*(st->buf));
    }
    *(st->buf) = tmp;
    *(st->bcap) = nc;
    return 0;
}

int append_char(t_pstate *st, char ch)
{
    if (ensure_capacity(st, *(st->blen) + 1) < 0)
        return -1;
    (*(st->buf))[(*(st->blen))++] = ch;
    return 0;
}

size_t skip_spaces(const char *line, size_t i, size_t len)
{
    while (i < len && is_space(line[i]))
        i++;
    return i;
}