/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_retrieval.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:24:06 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/10 17:51:16 by lgrigore         ###   ########.fr       */
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
		free(list->head);
		list->head = NULL;
		list->tail = NULL;
		list->size--;
		return (val);
	}
	current = list->head;
	prev = NULL;
	while (current->next)
	{
		prev = current;
		current = current->next;
	}
	val = current->value;
	free(current);
	prev->next = NULL;
	list->tail = prev;
	list->size--;
	return (val);
}
