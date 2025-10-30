/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:45:17 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/24 07:14:31 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_INTERNAL_H
#define TOKENIZER_INTERNAL_H

#include "../include/lexer.h"
#include "../external/libft/libft.h"
#include <stdlib.h>

/* Estructuras */
struct s_token
{
    t_token_type    type;
    char            *value;
};

typedef struct s_pstate 
{
    const char *line;
    size_t *i;
    size_t len;
    char **buf;
    size_t *bcap;
    size_t *blen;
} t_pstate;

typedef struct s_lstate 
{
    const char *line;
    size_t *i;
    size_t len;
    t_gen_list *tokens_list;
    bool next_is_redir_arg_val;
    bool expect_cmd_val;
    bool *next_is_redir_arg;
    bool *expect_cmd;
} t_lstate;

/* lexer_token.c */
t_token *create_token(t_token_type type, char *value);
void destroy_token(t_token *token);

/* lexer_utils.c */
char *ft_strndup(const char *s, size_t n);
int is_space(char c);
int is_operator_char(char c);
int match_two_char_op(const char *s, size_t pos, const char *op);
t_token_type operator_type(const char *op, size_t len);

/* lexer_parse_utils.c */
void pstate_init(t_pstate *st, const char *line, size_t *i, size_t len, 
    char **buf, size_t *bcap, size_t *blen);
int ensure_capacity(t_pstate *st, size_t need);
int append_char(t_pstate *st, char ch);
size_t skip_spaces(const char *line, size_t i, size_t len);

/* lexer_parse_quotes.c */
int parse_single_quote(t_pstate *st);
int parse_double_quote(t_pstate *st);
int parse_backslash_escape(t_pstate *st);
int parse_word_loop(t_pstate *st);
int handle_loop_char(t_pstate *st);

/* lexer_parse_word.c */
int parse_word(const char *line, size_t *i, size_t len, char **out_word);
int build_out_word(t_pstate *st, size_t start, char **out_word);
int finalize_parse_word(t_pstate *st, char *buf, size_t start, char **out_word);

/* lexer_operators.c */
int push_two_char_op(const char *line, size_t *i, t_gen_list *tokens_list, bool *next_is_redir_arg);
int push_one_char_op(const char *line, size_t *i, t_gen_list *tokens_list, bool *next_is_redir_arg, bool *expect_cmd);

/* lexer_process.c */
int process_next_token(t_lstate *ls);
int parse_word_and_push(t_lstate *ls);
int lexer_init_state(const char *line, t_gen_list *tokens_list, size_t *i, t_lstate *ls);
int run_token_loop(t_lstate *ls);
t_token_type determine_type_and_clear(t_lstate *ls);

#endif