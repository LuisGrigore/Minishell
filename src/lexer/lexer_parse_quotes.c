/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:00:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/07 00:07:03 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

#include "../include/environment.h"

static int expand_variable(t_pstate *st)
{
    size_t idx = *(st->i);
    size_t name_start = idx + 1;
    size_t name_len = 0;
    char *name = NULL;
    char *value = NULL;
    size_t k;

    if (name_start >= st->len)
    {
        /* lone '$' at end: treat as literal */
        if (append_char(st, '$') < 0)
            return -1;
        (*(st->i))++;
        return 1;
    }
    /* handle ${VAR} */
    if (st->line[name_start] == '{')
    {
        size_t j = name_start + 1;
        while (j < st->len && st->line[j] != '}')
            j++;
        if (j >= st->len)
        {
            /* no closing brace: treat '$' literally */
            if (append_char(st, '$') < 0)
                return -1;
            (*(st->i))++;
            return 1;
        }
        name_len = j - (name_start + 1);
        name = ft_strndup(st->line + name_start + 1, name_len);
        if (!name)
            return -1;
        (*(st->i)) = j + 1;
    }
    else
    {
        /* simple name: alnum or _ or ? */
        if (st->line[name_start] == '?')
        {
            name = ft_strdup("?");
            if (!name) return -1;
            (*(st->i)) += 2;
        }
        else
        {
            size_t j = name_start;
            while (j < st->len && (ft_isalnum(st->line[j]) || st->line[j] == '_'))
                j++;
            name_len = j - name_start;
            if (name_len == 0)
            {
                /* no valid var name: treat '$' as literal */
                if (append_char(st, '$') < 0)
                    return -1;
                (*(st->i))++;
                return 1;
            }
            name = ft_strndup(st->line + name_start, name_len);
            if (!name)
                return -1;
            (*(st->i)) = j;
        }
    }

    if (st->env && name)
        value = env_get(st->env, name);
    if (name)
        free(name);
    if (!value)
        return 1; /* undefined var expands to empty string */
    k = 0;
    while (value[k])
    {
        if (append_char(st, value[k]) < 0)
        {
            free(value);
            return -1;
        }
        k++;
    }
    free(value);
    return 1;
}

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
            /* In double quotes, backslash escapes the next char (", $, `, \\)
             * for simplicity we append next char as-is (existing behavior). */
            if (append_char(st, st->line[*(st->i) + 1]) < 0)
                return -1;
            *(st->i) += 2;
        }
        else if (st->line[*(st->i)] == '$')
        {
            if (expand_variable(st) < 0)
                return -1;
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
    if (c == '$')
    {
        r = expand_variable(st);
        if (r < 0)
            return -1;
        return 1;
    }
    if (append_char(st, c) < 0)
        return -1;
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