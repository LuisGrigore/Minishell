/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:24:35 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/10 19:01:49 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"



/* Refactored version with smaller helper functions */

/* NOTE: This is only a skeleton refactor of add_word_token.
   You must integrate it into your project and adjust prototypes,
   includes, and supporting functions accordingly. */


/* ------------------------------- UTILS ------------------------------- */

static char *append_segment(char *buf, char *seg)
{
    char *tmp;

    if (!seg)
        return buf;
    tmp = ft_strjoin(buf, seg);
    free(buf);
    free(seg);
    return tmp;
}

static char *append_literal_char(char *buf, char c)
{
    char s[2];
    s[0] = c;
    s[1] = '\0';
    return append_segment(buf, ft_strdup(s));
}

/* ----------------------------- SINGLE QUOTES ----------------------------- */

static int handle_single_quoted_segment(char *p, size_t *i, char **buf)
{
    size_t start;
    char *seg;

    *i = *i + 1;
    start = *i;
    while (p[*i] && p[*i] != '\'')
        *i = *i + 1;
    if (!p[*i])
        return LEXER_UNCLOSED_QUOTE_ERR;
    seg = ft_strndup(&p[start], *i - start);
    if (!seg)
        return MS_ALLOCATION_ERR;
    *buf = append_segment(*buf, seg);
    if (!*buf)
        return MS_ALLOCATION_ERR;
    *i = *i + 1;
    return MS_OK;
}

/* ----------------------------- VAR EXPANSION ----------------------------- */

static int expand_variable(t_environment *env, char *p, size_t *i, char **buf)
{
    char name[256];
    size_t j;
    char *var;

    j = 0;
    if (p[*i] == '?')
    {
        var = env_get(env, "?");
        *i = *i + 1;
        if (var)
        {
            *buf = append_segment(*buf, var);
            if (!*buf)
                return MS_ALLOCATION_ERR;
        }
        return MS_OK;
    }
    while (p[*i] && (ft_isalnum(p[*i]) || p[*i] == '_') && j + 1 < sizeof(name))
    {
        name[j] = p[*i];
        j = j + 1;
        *i = *i + 1;
    }
    name[j] = '\0';
    if (j == 0)
    {
        *buf = append_literal_char(*buf, '$');
        return (*buf ? MS_OK : MS_ALLOCATION_ERR);
    }
    var = env_get(env, name);
    if (var)
    {
        *buf = append_segment(*buf, var);
        if (!*buf)
            return MS_ALLOCATION_ERR;
    }
    return MS_OK;
}

/* ----------------------------- DOUBLE QUOTES ----------------------------- */

static int process_double_quoted_chunk(t_environment *env, char *p, size_t *i, char **buf)
{
    size_t start;
    char *seg;
    int status;

    *i = *i + 1;
    start = *i;
    while (p[*i] && p[*i] != '"')
    {
        if (p[*i] == '$')
        {
            if (*i > start)
            {
                seg = ft_strndup(&p[start], *i - start);
                if (!seg)
                    return MS_ALLOCATION_ERR;
                *buf = append_segment(*buf, seg);
                if (!*buf)
                    return MS_ALLOCATION_ERR;
            }
            *i = *i + 1;
            status = expand_variable(env, p, i, buf);
            if (status != MS_OK)
                return status;
            start = *i;
            continue;
        }
        *i = *i + 1;
    }
    if (!p[*i])
        return LEXER_UNCLOSED_QUOTE_ERR;
    if (*i > start)
    {
        seg = ft_strndup(&p[start], *i - start);
        if (!seg)
            return MS_ALLOCATION_ERR;
        *buf = append_segment(*buf, seg);
        if (!*buf)
            return MS_ALLOCATION_ERR;
    }
    *i = *i + 1;
    return MS_OK;
}

/* --------------------------- UNQUOTED CHUNK --------------------------- */

static int process_unquoted_chunk(t_environment *env, char *p, size_t *i, char **buf)
{
    size_t start;
    char *seg;
    int status;

    start = *i;
    while (p[*i] && !is_space(p[*i]) && !is_operator_char(p[*i]) && p[*i] != '\'' && p[*i] != '"' && p[*i] != '$')
        *i = *i + 1;
    if (*i > start)
    {
        seg = ft_strndup(&p[start], *i - start);
        if (!seg)
            return MS_ALLOCATION_ERR;
        *buf = append_segment(*buf, seg);
        if (!*buf)
            return MS_ALLOCATION_ERR;
    }
    if (p[*i] == '$')
    {
        *i = *i + 1;
        status = expand_variable(env, p, i, buf);
        return status;
    }
    return MS_OK;
}

/* ----------------------------- MAIN WORD BUILDER ----------------------------- */

static int build_word(t_environment *env, char *p, size_t *i, char **buf)
{
    int status;

    while (p[*i] && !is_space(p[*i]) && !is_operator_char(p[*i]))
    {
        if (p[*i] == '\'')
        {
            status = handle_single_quoted_segment(p, i, buf);
            if (status != MS_OK)
                return status;
        }
        else if (p[*i] == '"')
        {
            status = process_double_quoted_chunk(env, p, i, buf);
            if (status != MS_OK)
                return status;
        }
        else
        {
            status = process_unquoted_chunk(env, p, i, buf);
            if (status != MS_OK)
                return status;
        }
    }
    return MS_OK;
}

/* ------------------------------ PUBLIC ENTRY ------------------------------ */

int add_word_token(char **current_char, t_gen_list *tokens, char *line, t_environment *env)
{
    char *p;
    char *buf;
    size_t i;
    int status;
    t_token *token;

    if (!current_char || !*current_char || !tokens)
        return LEXER_NULL_ERR;
    p = *current_char;
    i = 0;
    buf = ft_strdup("");
    if (!buf)
        return MS_ALLOCATION_ERR;
    status = build_word(env, p, &i, &buf);
    if (status != MS_OK)
    {
        free(buf);
        return status;
    }
    *current_char = p + i;
    if (*buf == '\0')
    {
        free(buf);
        return MS_OK;
    }
    token = create_token(TOKEN_WORD, buf);
    if (!token)
    {
        free(buf);
        return MS_ALLOCATION_ERR;
    }
    gen_list_push_back(tokens, token);
    return MS_OK;
}


int add_operator_token(char **current_char, t_gen_list *tokens, char *line)
{
	size_t start;
	size_t end;
	char *value;
	t_token *token;

	start = 0;
	end = start;
	while (is_operator_char(line[end]))
		end++;
	value = ft_strndup(&line[start], end - start);
	if (!value)
		return (MS_ALLOCATION_ERR);
	token = create_token(operator_type(value, end - start), value);
	if (!token)
		return (free(value), MS_ALLOCATION_ERR);
	gen_list_push_back(tokens, token);
	*current_char += (end - start);
	return (MS_OK);
}

bool is_word_start_char(char c)
{
	return (!is_space(c) && !is_operator_char(c) && c != '\0');
}

int tokenize_aux(char *current_char, t_gen_list *tokens, char *line, t_environment *env)
{
    int status_code;
    
    if (!current_char || !tokens || !line)
        return (LEXER_NULL_ERR);
    while (*current_char && is_space(*current_char))
        current_char++;
        if (*current_char == '\0')
        return (MS_OK);
    if (is_word_start_char(*current_char))
        status_code = add_word_token(&current_char, tokens, current_char, env);
    else if (is_operator_char(*current_char))
        status_code = add_operator_token(&current_char, tokens, current_char);
    else
        return (LEXER_UNSUPORTED_CHARACTER_ERR);

    if (status_code != MS_OK)
        return (status_code);
    return (tokenize_aux(current_char, tokens, line, env));
}

int new_tokenize_line(char *line, t_gen_list *tokens, t_environment *env)
{
	return (tokenize_aux(line, tokens, line, env));
}