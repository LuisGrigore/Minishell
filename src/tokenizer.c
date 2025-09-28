#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/list.h"
#include "../include/tokenizer.h" 
#include "../libft/libft.h"
#include "../include/util.h"


static char *ft_strndup(const char *s, size_t n) {
    char *p = malloc(n + 1); size_t i; if (!p) return NULL;
    for (i = 0; i < n && s[i]; i++) p[i] = s[i]; p[i] = '\0'; return p;
}

static int is_space(char c) { return c == ' ' || c == '\t'; }
static int is_operator_char(char c) { return c == '|' || c == '>' || c == '<'; }
static int match_two_char_op(const char *s, size_t pos, const char *op) {
    return s[pos] && s[pos+1] && s[pos] == op[0] && s[pos+1] == op[1];
}

static t_token *create_token(t_token_type type, char *value) {
    t_token *tok = malloc(sizeof(t_token));
    if (!tok) return NULL;
    tok->type = type;
    tok->value = value;
    return tok;
}

static t_token_type operator_type(const char *op, size_t len) {
    if (len == 1) {
        if (op[0] == '|') return TOKEN_PIPE;
        if (op[0] == '<') return TOKEN_REDIR_IN;
        if (op[0] == '>') return TOKEN_REDIR_OUT;
    } else if (len == 2) {
        if (op[0] == '<' && op[1] == '<') return TOKEN_HEREDOC;
        if (op[0] == '>' && op[1] == '>') return TOKEN_REDIR_APPEND;
    }
    return TOKEN_ARG; // fallback
}

t_gen_list *tokenize(const char *line) {
    size_t i = 0, len = ft_strlen(line);
    t_gen_list *tokens_list = init_list();
    if (!tokens_list) return NULL;

    bool expect_cmd = true; // El siguiente token no operador será CMD

    while (i < len) {
        while (i < len && is_space(line[i])) i++;
        if (i >= len) break;

        /* operadores de dos caracteres */
        if (match_two_char_op(line, i, ">>") || match_two_char_op(line, i, "<<")) {
            char *op = ft_strndup(line + i, 2);
            t_token *tok = create_token(operator_type(op, 2), op);
            push_end(tokens_list, tok);
            i += 2;
            continue;
        }

        /* operadores de un caracter */
        if (is_operator_char(line[i])) {
            char *op = ft_strndup(line + i, 1);
            t_token *tok = create_token(operator_type(op, 1), op);
            push_end(tokens_list, tok);
            i++;
            if (tok->type == TOKEN_PIPE || tok->type == TOKEN_REDIR_IN ||
                tok->type == TOKEN_REDIR_OUT || tok->type == TOKEN_REDIR_APPEND ||
                tok->type == TOKEN_HEREDOC)
                expect_cmd = true; // después de operador esperamos comando
            continue;
        }

        /* palabras */
        size_t start = i;
        char *buf = NULL; size_t bcap = 0, blen = 0;

        while (i < len && !is_space(line[i]) && !is_operator_char(line[i])) {
            char c = line[i];
            // Manejo de comillas simples, dobles y escapes (igual que antes)
            if (c == '\'') { i++; while(i<len && line[i]!='\''){ if(blen+1>=bcap){ size_t nc=(bcap?bcap*2:64); char*tmp=realloc(buf,nc); buf=tmp;bcap=nc;} buf[blen++]=line[i++]; } if(i<len&&line[i]=='\'') i++; }
            else if(c=='"'){ i++; while(i<len && line[i]!='"'){ if(line[i]=='\\'&&i+1<len){ if(blen+1>=bcap){ size_t nc=(bcap?bcap*2:64); char*tmp=realloc(buf,nc); buf=tmp;bcap=nc; } buf[blen++]=line[i+1]; i+=2; } else { if(blen+1>=bcap){ size_t nc=(bcap?bcap*2:64); char*tmp=realloc(buf,nc); buf=tmp;bcap=nc;} buf[blen++]=line[i++]; } } if(i<len&&line[i]=='"') i++; }
            else if(c=='\\'&&i+1<len){ if(blen+1>=bcap){ size_t nc=(bcap?bcap*2:64); char*tmp=realloc(buf,nc); buf=tmp;bcap=nc;} buf[blen++]=line[i+1]; i+=2; }
            else{ if(blen+1>=bcap){ size_t nc=(bcap?bcap*2:64); char*tmp=realloc(buf,nc); buf=tmp;bcap=nc;} buf[blen++]=c; i++; }
        }

        char *word;
        if(blen==0){ size_t wlen=i-start; word=ft_strndup(line+start,wlen); if(!word) goto error; }
        else { word=malloc(blen+1); if(!word) goto error; for(size_t k=0;k<blen;k++) word[k]=buf[k]; word[blen]='\0'; free(buf); }

        t_token_type type = expect_cmd ? TOKEN_CMD : TOKEN_ARG;
        expect_cmd = false; // ya marcamos comando si tocaba

        t_token *tok = create_token(type, word);
        push_end(tokens_list, tok);
    }

    return tokens_list;

error:
    if(tokens_list) destroy_gen_list(tokens_list, free);
    return NULL;
}
