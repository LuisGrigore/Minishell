/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:39:46 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/25 21:01:21 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/list.h"
#include "../include/parser.h"

// t_token *create_token(t_tokens type, const char *value) {
//     t_token *new = malloc(sizeof(t_token));
//     if (!new) return (NULL);
//     new->type = type;
//     new->value = strdup(value);
//     return (new);
// }

// void destroy_token(void *ptr) {
//     t_token *tok = (t_token *)ptr;
//     if (tok->value)
//         free(tok->value);
//     free(tok);
// }