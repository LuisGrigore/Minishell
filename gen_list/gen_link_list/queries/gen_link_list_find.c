/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_find.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:46:01 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/30 23:48:16 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

void	*gen_list_find(t_gen_list *list, t_predicate predicate)
{
	t_node	*current;

	if (!list || !predicate)
		return (NULL);
	current = list->head;
	while (current)
	{
		if (predicate(current->value))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	*gen_list_find_ctx(t_gen_list *list, t_predicate_ctx predicate,
		void *context)
{
	t_node	*curr;

	curr = list->head;
	while (curr)
	{
		if (predicate(curr->value, context))
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
