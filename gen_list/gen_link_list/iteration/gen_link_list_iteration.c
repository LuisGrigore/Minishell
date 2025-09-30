/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_iteration.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:56:57 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/30 14:57:29 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

// TODO :: crear un funcion igual pero prev en vez de next.
void *gen_list_iter_next(t_gen_list_iter *it)
{
    void *val;
    if (!it || !it->current)
        return NULL;
    val = it->current->value;
    it->current = it->current->next;
    return val;
}

void gen_list_for_each(t_gen_list *list, t_apply_func func)
{
    t_gen_list_iter *it;
    void *val;

    if (!list || !func)
        return;
    it = gen_list_iter_start(list);
    while ((val = gen_list_iter_next(it)))
        func(val);
    gen_list_iter_destroy(it);
}

void gen_list_for_each_ctx(t_gen_list *list, t_apply_func_ctx func, void *context)
{
    t_gen_list_iter *it;
    void *val;

    if (!list || !func)
        return;

    it = gen_list_iter_start(list);
    if (!it)
        return;

    while ((val = gen_list_iter_next(it)))
        func(val, context);

    gen_list_iter_destroy(it);
}
