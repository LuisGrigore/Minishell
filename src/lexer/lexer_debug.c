#include "lexer_internal.h"
#include <stdio.h>

void	print_tokens(t_gen_list *tokens)
{
	t_gen_list_iter *it;
	t_token *tok;
	const char *type_str;

	if (!tokens)
		return ;
	it = gen_list_iter_start(tokens);
	while ((tok = (t_token *)gen_list_iter_next(it)) != NULL)
	{
		switch (tok->type)
		{
		case TOKEN_WORD:
			type_str = "WORD";
			break ;
		case TOKEN_PIPE:
			type_str = "PIPE";
			break ;
		case TOKEN_REDIR_IN:
			type_str = "REDIR_IN";
			break ;
		case TOKEN_REDIR_OUT:
			type_str = "REDIR_OUT";
			break ;
		case TOKEN_REDIR_APPEND:
			type_str = "REDIR_APPEND";
			break ;
		case TOKEN_HEREDOC:
			type_str = "HEREDOC";
			break ;
		default:
			type_str = "UNKNOWN";
			break ;
		}
		printf("[%s] : [%s]\n", type_str, tok->value);
	}
}