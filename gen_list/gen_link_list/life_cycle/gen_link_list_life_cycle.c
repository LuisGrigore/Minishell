/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_life_cycle.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:55:37 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/30 23:27:47 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_link_list_internal.h"

t_gen_list	*gen_list_create(void)
{
	t_gen_list	*list;

	list = malloc(sizeof(t_gen_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

void	gen_list_destroy(t_gen_list *list,
		t_element_destroyer element_destroyer)
{
	t_node	*current;
	t_node	*tmp;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		tmp = current->next;
		if (element_destroyer)
			value_destroyer(current->value);
		free(current);
		current = tmp;
	}
	free(list);
}
