#include "lexer_internal.h"
t_token_type lexer_get_token_type(t_token * token)
{
	return (token->type);
}
char *lexer_get_token_content(t_token * token)
{
	if(!token || !token->value)
		return(NULL);
	return (token->value);
}
bool lexer_is_token_type(t_token * token, t_token_type type)
{
	return(lexer_get_token_type(token) == type);
}