
#include "lexer_internal.h"

char *ft_strndup(const char *s, size_t n) 
{
    char *p;
    size_t i;
    
    p = NULL;
    p = malloc(n + 1);
    i = 0;
    if (!p) 
        return (NULL);
    while (i < n && s[i]) {
        p[i] = s[i];
        i++;
    }
    p[i] = '\0';
    return (p);
}

int is_space(char c) 
{ 
    if (c == ' ' || c == '\t')
        return (1) ;
    return (0);
}
int is_operator_char(char c)
{
    if (c == '|')
        return (1);
    if (c == '>')
        return (1);
    if (c == '<')
        return (1);
    return (0);
}

int match_two_char_op(const char *s, size_t pos, const char *op)
{
    size_t slen;
    size_t olen;

    if (!s || !op)
        return 0;
    slen = ft_strlen(s);
    olen = ft_strlen(op);
    if (pos + 1 >= slen || olen < 2)
        return (0);
    if (s[pos] == op[0])
    {
        if (s[pos + 1] == op[1])
            return (1);
        return (0);
    }
    return (0);
}



t_token_type operator_type(const char *op, size_t len) {
    if (len == 1) 
    {
        if (op[0] == '|') 
            return (TOKEN_PIPE);
        if (op[0] == '<') 
            return (TOKEN_REDIR_IN);
        if (op[0] == '>') 
            return (TOKEN_REDIR_OUT);
    } else if (len == 2) 
    {
        if (op[0] == '<' && op[1] == '<') 
            return (TOKEN_HEREDOC);
        if (op[0] == '>' && op[1] == '>') 
            return (TOKEN_REDIR_APPEND);
    }
    return (TOKEN_ARG); // fallback
}