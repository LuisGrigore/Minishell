/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_insertion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:23:46 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/05 22:11:08 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

t_gen_list_status_code	gen_list_push_back(t_gen_list *list, void *value)
{
	t_node	*node;

	if (!list)
		return GEN_LIST_IS_NULL_ERR;
	node = malloc(sizeof(t_node));
	if (!node)
		return (GEN_LIST_MALLOC_ERR);
	node->value = value;
	node->next = NULL;
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
	return (GEN_LIST_OK);
}

t_gen_list_status_code	gen_list_push_front(t_gen_list *list, void *value)
{
	t_node	*node;

	if (!list)
		return GEN_LIST_IS_NULL_ERR;
	node = malloc(sizeof(t_node));
	if (!node)
		return (GEN_LIST_MALLOC_ERR);
	node->value = value;
	node->next = list->head;
	list->head = node;
	if (!list->tail)
		list->tail = node;
	list->size++;
	return (GEN_LIST_OK);
}
