/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_retrieval.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:24:06 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 19:44:05 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

// TODO pop_back

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

void	*gen_list_pop_back(t_gen_list *list)
{
	t_node	*current;
	t_node	*prev;
	void	*val;

	if (!list || !list->head)
		return (NULL);
	if (!list->head->next)
	{
		val = list->head->value;
		list->head = NULL;
		list->tail = NULL;
		return (list->size--, free(list->head), val);
	}
	current = list->head;
	prev = NULL;
	while (current->next)
	{
		prev = current;
		current = current->next;
	}
	val = current->value;
	prev->next = NULL;
	list->tail = prev;
	return (list->size--, free(current), val);
}
