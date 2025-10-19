/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_predicates.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:45:30 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/01 00:29:45 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

bool	gen_list_is_empty(t_gen_list *list)
{
	return (list->size == 0);
}

bool	gen_list_has(t_gen_list *list, t_predicate predicate)
{
	return (gen_list_find(list, predicate) != NULL);
}

bool	gen_list_has_ctx(t_gen_list *list, t_predicate_ctx predicate,
		void *context)
{
	return (gen_list_find_ctx(list, predicate, context) != NULL);
}
