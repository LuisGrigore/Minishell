/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_iteration.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:56:57 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/28 19:38:49 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

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

t_gen_list_status_code	gen_list_for_each(t_gen_list *list, t_apply_func func)
{
	t_gen_list_iter	*it;
	void			*val;

	if (!list || !func)
		return (GEN_LIST_IS_NULL_ERR);
	it = gen_list_iter_start(list);
	if (!it)
		return (GEN_LIST_MALLOC_ERR);
	val = gen_list_iter_next(it);
	while (val)
	{
		func(val);
		val = gen_list_iter_next(it);
	}
	gen_list_iter_destroy(it);
	return (GEN_LIST_OK);
}

t_gen_list_status_code	gen_list_for_each_ctx(t_gen_list *list,
		t_apply_func_ctx func, void *context)
{
	t_gen_list_iter	*it;
	void			*val;

	if (!list || !func)
		return (GEN_LIST_IS_NULL_ERR);
	it = gen_list_iter_start(list);
	if (!it)
		return (GEN_LIST_MALLOC_ERR);
	val = gen_list_iter_next(it);
	while (val)
	{
		func(val, context);
		val = gen_list_iter_next(it);
	}
	gen_list_iter_destroy(it);
	return (GEN_LIST_OK);
}
