/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_iteration_life_cycle.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:56:57 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/30 23:27:35 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

// TODO:: hacer que reciba un bool que decida si se empieza por el final o el 
//principio, hay que hacer que la lista sea doblemente enlazada.
t_gen_list_iter	*gen_list_iter_start(t_gen_list *list)
{
    t_gen_list_iter *it;
	
	it = malloc(sizeof(t_gen_list_iter));
    if (!it)
        return NULL;
    it->current = list ? list->head : NULL;
    return it;
}

void	gen_list_iter_destroy(t_gen_list_iter *it)
{
    free(it);
}
