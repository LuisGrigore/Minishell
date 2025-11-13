/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_peek.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:45:56 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 19:35:15 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

// TODO :: implementar todas las funciones de peek

void	*gen_list_peek_top(t_gen_list *list)
{
	if (!list || gen_list_is_empty(list))
		return (NULL);
	return (list->head->value);
}

void	*gen_list_peek_bottom(t_gen_list *list)
{
	if (!list || gen_list_is_empty(list))
		return (NULL);
	return (list->tail->value);
}

void	*gen_list_peek_index(t_gen_list *list, int idx)
{
	t_gen_list_iter	*it;
	int				i;
	void			*result;

	it = gen_list_iter_start(list);
	i = 0;
	result = NULL;
	result = gen_list_iter_next(it);
	while (result != NULL)
	{
		if (i == idx)
		{
			break ;
		}
		i++;
		result = gen_list_iter_next(it);
	}
	gen_list_iter_destroy(it);
	return (result);
}
