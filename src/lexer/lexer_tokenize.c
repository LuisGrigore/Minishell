/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:09:07 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/19 20:43:01 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"
static size_t skip_spaces(const char *line, size_t i, size_t len)
{
	while (i < len && is_space(line[i]))
		i++;
	return i;
}

static int push_two_char_op(const char *line, size_t *i,
	t_gen_list *tokens_list, bool *next_is_redir_arg)
{
	char *op;
	t_token *tok;

	if (!match_two_char_op(line, *i, ">>") && !match_two_char_op(line, *i, "<<"))
		return 0; /* not handled */
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

static int push_one_char_op(const char *line, size_t *i,
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

/* parse_word: allocate *out_word, advance *i. Returns 1 on success,
   -1 on allocation error, -2 on unclosed quote syntax error. */
typedef struct s_pstate {
	const char *line;
	size_t *i;
	size_t len;
	char **buf;
	size_t *bcap;
	size_t *blen;
} t_pstate;

static int ensure_capacity(t_pstate *st, size_t need)
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

static int append_char(t_pstate *st, char ch)
{
	if (ensure_capacity(st, *(st->blen) + 1) < 0)
		return -1;
	(*(st->buf))[(*(st->blen))++] = ch;
	return 0;
}

static int parse_single_quote(t_pstate *st)
{
	(*(st->i))++;
	while (*(st->i) < st->len && st->line[*(st->i)] != '\'') {
		if (append_char(st, st->line[*(st->i)]) < 0)
			return -1;
		(*(st->i))++;
	}
	if (*(st->i) >= st->len || st->line[*(st->i)] != '\'')
		return -2;
	(*(st->i))++;
	return 1;
}

static int parse_double_quote(t_pstate *st)
{
	(*(st->i))++;
	while (*(st->i) < st->len && st->line[*(st->i)] != '"') {
		if (st->line[*(st->i)] == '\\' && *(st->i) + 1 < st->len) {
			if (append_char(st, st->line[*(st->i) + 1]) < 0)
				return -1;
			*(st->i) += 2;
		} else {
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

static int parse_backslash_escape(t_pstate *st)
{
	if (*(st->i) + 1 >= st->len)
		return 0;
	if (append_char(st, st->line[*(st->i) + 1]) < 0)
		return -1;
	*(st->i) += 2;
	return 1;
}

static int parse_word_loop(t_pstate *st)
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

static int handle_loop_char(t_pstate *st)
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
	(*(st->i))++;
	return 1;
}

static int build_out_word(t_pstate *st, size_t start, char **out_word)
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

static int parse_word(const char *line, size_t *i, size_t len, char **out_word)
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

static void pstate_init(t_pstate *st, const char *line, size_t *i, size_t len,
	char **buf, size_t *bcap, size_t *blen)
{
	st->line = line;
	st->i = i;
	st->len = len;
	st->buf = buf;
	st->bcap = bcap;
	st->blen = blen;
}

static int finalize_parse_word(t_pstate *st, char *buf, size_t start, char **out_word)
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

typedef struct s_lstate {
	const char *line;
	size_t *i;
	size_t len;
	t_gen_list *tokens_list;
	bool next_is_redir_arg_val;
	bool expect_cmd_val;
	bool *next_is_redir_arg;
	bool *expect_cmd;
} t_lstate;

static int process_next_token(t_lstate *ls)
{
	return MS_OK; /* placeholder, replaced by helpers below */
}

static int skip_and_check_eof(t_lstate *ls)
{
	*(ls->i) = skip_spaces(ls->line, *(ls->i), ls->len);
	if (*(ls->i) >= ls->len)
		return MS_OK;
	return 0;
}

static int try_two_char_ops(t_lstate *ls)
{
	int r;

	r = push_two_char_op(ls->line, ls->i, ls->tokens_list, ls->next_is_redir_arg);
	if (r < 0)
		return LEXER_ERR;
	if (r == 1)
		return MS_OK;
	return 0;
}

static int try_one_char_ops(t_lstate *ls)
{
	int r;

	r = push_one_char_op(ls->line, ls->i, ls->tokens_list, ls->next_is_redir_arg, ls->expect_cmd);
	if (r < 0)
		return LEXER_ERR;
	if (r == 1)
		return MS_OK;
	return 0;
}

static int parse_word_and_push(t_lstate *ls)
{
	return MS_OK; /* replaced by helpers below */
}

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

static t_token_type determine_type_and_clear(t_lstate *ls)
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

/* Rebuild parse_word_and_push to use the small helpers */
static int parse_word_and_push(t_lstate *ls)
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

/* Rebuild process_next_token to call small helpers */
static int process_next_token(t_lstate *ls)
{
	int r;

	r = skip_and_check_eof(ls);
	if (r == MS_OK)
		return MS_OK;
	r = try_two_char_ops(ls);
	if (r == MS_OK || r == LEXER_ERR)
		return r;
	r = try_one_char_ops(ls);
	if (r == MS_OK || r == LEXER_ERR)
		return r;
	return parse_word_and_push(ls);
}

int lexer_tokenize(const char *line, t_gen_list *tokens_list)
{
	size_t i;
	t_lstate ls;
	int r;

	i = 0;
	r = lexer_init_state(line, tokens_list, &i, &ls);
	if (r != MS_OK)
		return r;
	return run_token_loop(&ls);
}

static int lexer_init_state(const char *line, t_gen_list *tokens_list,
	size_t *i, t_lstate *ls)
{
	if (!tokens_list)
		return LEXER_NULL_ERR;
	*i = 0;
	ls->line = line;
	ls->i = i;
	ls->len = ft_strlen(line);
	ls->tokens_list = tokens_list;
	ls->expect_cmd_val = true;
	ls->next_is_redir_arg_val = false;
	ls->next_is_redir_arg = &ls->next_is_redir_arg_val;
	ls->expect_cmd = &ls->expect_cmd_val;
	return MS_OK;
}

static int run_token_loop(t_lstate *ls)
{
	int r;

	while (*(ls->i) < ls->len)
	{
		r = process_next_token(ls);
		if (r == LEXER_SYNTAX_ERR)
			return LEXER_SYNTAX_ERR;
		if (r == LEXER_ERR)
		{
			if (ls->tokens_list)
				gen_list_destroy(ls->tokens_list, free);
			return LEXER_ERR;
		}
	}
	return MS_OK;
}


