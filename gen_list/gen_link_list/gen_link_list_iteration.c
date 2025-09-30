/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_iteration.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:56:57 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/30 14:09:40 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_link_list_internal.h"

// TODO:: hacer que reciba un bool que decida si se empieza por el final o el principio, hay que hacer que la lista sea doblemente enlazada.
t_gen_list_iter	gen_list_iter_start(t_gen_list *list)
{
	t_gen_list_iter	it;

	it.current = list ? list->head : NULL;
	return (it);
}
// TODO :: crear un funcion igual pero prev en vez de next.
void	*gen_list_iter_next(t_gen_list_iter *it)
{
	void	*val;

	if (!it || !it->current)
		return (NULL);
	val = it->current->value;
	it->current = it->current->next;
	return (val);
}

void	gen_list_for_each(t_gen_list *list, t_apply_func func)
{
	t_gen_list_iter	it;
	void			*val;

	if (!list || !func)
		return ;
	it = gen_list_iter_start(list);
	while ((val = gen_list_iter_next(&it)))
		func(val);
}

void	gen_list_for_each_ctx(t_gen_list *list, t_apply_func_ctx func,
		void *context)
{
	t_gen_list_iter	it;
	void			*val;

	if (!list || !func)
		return ;
	it = gen_list_iter_start(list);
	while ((val = gen_list_iter_next(&it)))
		func(val, context);
}
