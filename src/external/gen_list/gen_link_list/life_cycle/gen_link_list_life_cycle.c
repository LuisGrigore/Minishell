/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_life_cycle.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:55:37 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/01 14:05:39 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

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

void gen_list_destroy(t_gen_list *list, t_element_destroyer element_destroyer)
{
	
    if (!list)
        return ;
    while (list->size > 0)
	{
        element_destroyer(gen_list_pop_front(list));
	}
	free(list);
}
