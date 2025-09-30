/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_retrieval.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:24:06 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/30 23:24:08 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

void	*gen_list_pop_front(t_gen_list *list)
{
	t_node	*node;
	void	*val;

	if (!list || !list->head)
		return (NULL);
	node = list->head;
	val = node->value;
	list->head = node->next;
	if (!list->head)
		list->tail = NULL;
	free(node);
	list->size--;
	return (val);
}
