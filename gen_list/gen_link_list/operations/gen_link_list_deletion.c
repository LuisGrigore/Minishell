/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_deletion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:23:56 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/30 23:57:48 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

static void	remove_current_node(t_gen_list *list, t_node **current,
		t_node **prev, t_element_destroyer element_destroyer)
{
	t_node	*next;

	if (!list || !current || !*current)
		return ;
	next = (*current)->next;
	if (*prev)
		(*prev)->next = next;
	else
		list->head = next;
	if (*current == list->tail)
		list->tail = *prev;
	if (element_destroyer)
		element_destroyer((*current)->value);
	free(*current);
	list->size--;
	*current = next;
}

void	gen_list_remove_if(t_gen_list *list, t_predicate predicate,
		t_element_destroyer element_destroyer)
{
	t_node	*current;
	t_node	*prev;
	t_node	*next;
	bool	remove;

	if (!list || !predicate)
		return ;
	current = list->head;
	prev = NULL;
	while (current)
	{
		next = current->next;
		remove = predicate(current->value);
		if (remove)
			remove_current_node(list, &current, &prev, element_destroyer);
		else
		{
			prev = current;
			current = next;
		}
	}
}

void	gen_list_remove_if_ctx(t_gen_list *list, t_predicate_ctx predicate,
		void *context, t_element_destroyer element_destroyer)
{
	t_node	*current;
	t_node	*prev;
	t_node	*next;
	bool	remove;

	if (!list || !predicate)
		return ;
	current = list->head;
	prev = NULL;
	while (current)
	{
		next = current->next;
		remove = predicate(current->value, context);
		if (remove)
			remove_current_node(list, &current, &prev, element_destroyer);
		else
		{
			prev = current;
			current = next;
		}
	}
}
