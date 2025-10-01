/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_life_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:36:58 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/01 14:47:30 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_internal.h"

//private
void destroy_token(t_token *token)
{
    if (!token)
        return;

    if (token->value)
    {
        free(token->value);
        token->value = NULL;
    }

    free(token);
}

static void destroy_token_data(void *token_ptr)
{
	destroy_token((t_token *) token_ptr);
}

t_token *create_token(t_token_type type, char *value)
{
    t_token *tok = malloc(sizeof(t_token));
    if (!tok) return NULL;
    tok->type = type;
    tok->value = value;
    return tok;
}

//public
void 				lexer_destroy(t_gen_list *tokens)
{
	if(!tokens)
		return;
	gen_list_destroy(tokens, destroy_token_data);
}
