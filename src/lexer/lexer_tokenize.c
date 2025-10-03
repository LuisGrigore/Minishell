/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:09:07 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/01 14:57:04 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

t_gen_list *lexer_tokenize(const char *line) {
    size_t i = 0, len = ft_strlen(line);
    t_gen_list *tokens_list = gen_list_create();
    if (!tokens_list) return NULL;

    bool expect_cmd = true; // El siguiente token no operador será CMD
    bool next_is_redir_arg = false; // El siguiente token después de >, >>, <, <<

    while (i < len) {
        while (i < len && is_space(line[i])) i++;
        if (i >= len) break;

        /* operadores de dos caracteres */
        if (match_two_char_op(line, i, ">>") || match_two_char_op(line, i, "<<")) {
            char *op = ft_strndup(line + i, 2);
            t_token *tok = create_token(operator_type(op, 2), op);
            gen_list_push_back(tokens_list, tok);
            i += 2;

            if (tok->type == TOKEN_REDIR_APPEND || tok->type == TOKEN_HEREDOC)
                next_is_redir_arg = true;

            continue;
        }

        /* operadores de un caracter */
        if (is_operator_char(line[i])) {
            char *op = ft_strndup(line + i, 1);
            t_token *tok = create_token(operator_type(op, 1), op);
            gen_list_push_back(tokens_list, tok);
            i++;

            if (tok->type == TOKEN_REDIR_IN || tok->type == TOKEN_REDIR_OUT)
                next_is_redir_arg = true;
            else if (tok->type == TOKEN_PIPE)
                expect_cmd = true;

            continue;
        }

        /* palabras */
        size_t start = i;
        char *buf = NULL; size_t bcap = 0, blen = 0;

        while (i < len && !is_space(line[i]) && !is_operator_char(line[i])) {
            char c = line[i];
            if (c == '\'') { i++; while(i<len && line[i]!='\''){ if(blen+1>=bcap){ size_t nc=(bcap?bcap*2:64); char*tmp=realloc(buf,nc); buf=tmp;bcap=nc;} buf[blen++]=line[i++]; } if(i<len&&line[i]=='\'') i++; }
            else if(c=='"'){ i++; while(i<len && line[i]!='"'){ if(line[i]=='\\'&&i+1<len){ if(blen+1>=bcap){ size_t nc=(bcap?bcap*2:64); char*tmp=realloc(buf,nc); buf=tmp;bcap=nc; } buf[blen++]=line[i+1]; i+=2; } else { if(blen+1>=bcap){ size_t nc=(bcap?bcap*2:64); char*tmp=realloc(buf,nc); buf=tmp;bcap=nc;} buf[blen++]=line[i++]; } } if(i<len&&line[i]=='"') i++; }
            else if(c=='\\'&&i+1<len){ if(blen+1>=bcap){ size_t nc=(bcap?bcap*2:64); char*tmp=realloc(buf,nc); buf=tmp;bcap=nc;} buf[blen++]=line[i+1]; i+=2; }
            else{ if(blen+1>=bcap){ size_t nc=(bcap?bcap*2:64); char*tmp=realloc(buf,nc); buf=tmp;bcap=nc;} buf[blen++]=c; i++; }
        }

        char *word;
        if(blen==0){ size_t wlen=i-start; word=ft_strndup(line+start,wlen); if(!word) goto error; }
        else { word=malloc(blen+1); if(!word) goto error; for(size_t k=0;k<blen;k++) word[k]=buf[k]; word[blen]='\0'; free(buf); }

        t_token_type type;
        if (next_is_redir_arg) {
            type = TOKEN_ARG; // siempre argumento si viene después de redirección
            next_is_redir_arg = false;
        } else if (expect_cmd) {
            type = TOKEN_CMD;
            expect_cmd = false;
        } else {
            type = TOKEN_ARG;
        }

        t_token *tok = create_token(type, word);
        gen_list_push_back(tokens_list, tok);
    }

    return tokens_list;

error:
    if(tokens_list) gen_list_destroy(tokens_list, free);
    return NULL;
}


