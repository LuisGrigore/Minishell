/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_find.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:46:01 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/01 12:43:11 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

void	*gen_list_find(t_gen_list *list, t_predicate predicate)
{
	void			*value;
	t_gen_list_iter	*it;

	if (!list || !predicate)
		return (NULL);
	it = gen_list_iter_start(list);
	value = gen_list_iter_next(it);
	while (value)
	{
		if (predicate(value))
			return (value);
		value = gen_list_iter_next(it);
	}
	gen_list_iter_destroy(it);
	return (NULL);
}

void	*gen_list_find_ctx(t_gen_list *list, t_predicate_ctx predicate,
		void *context)
{
	void			*value;
	t_gen_list_iter	*it;

	if (!list || !predicate)
		return (NULL);
	it = gen_list_iter_start(list);
	value = gen_list_iter_next(it);
	while (value)
	{
		if (predicate(value, context))
		{
			gen_list_iter_destroy(it);
			return (value);
		}
		value = gen_list_iter_next(it);
	}
	gen_list_iter_destroy(it);
	return (NULL);
}
