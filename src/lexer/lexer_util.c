
#include "lexer_internal.h"

char *ft_strndup(const char *s, size_t n) {
    char *p = malloc(n + 1); size_t i; if (!p) return NULL;
    for (i = 0; i < n && s[i]; i++) p[i] = s[i]; p[i] = '\0'; return p;
}

int is_space(char c) { return c == ' ' || c == '\t'; }
int is_operator_char(char c) { return c == '|' || c == '>' || c == '<'; }
int match_two_char_op(const char *s, size_t pos, const char *op) {
    return s[pos] && s[pos+1] && s[pos] == op[0] && s[pos+1] == op[1];
}



t_token_type operator_type(const char *op, size_t len) {
    if (len == 1) 
    {
        if (op[0] == '|') return TOKEN_PIPE;
        if (op[0] == '<') return TOKEN_REDIR_IN;
        if (op[0] == '>') return TOKEN_REDIR_OUT;
    } else if (len == 2) 
    {
        if (op[0] == '<' && op[1] == '<') return TOKEN_HEREDOC;
        if (op[0] == '>' && op[1] == '>') return TOKEN_REDIR_APPEND;
    }
    return TOKEN_ARG; // fallback
}