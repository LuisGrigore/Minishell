/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:41 by dmaestro          #+#    #+#             */
/*   Updated: 2025/06/02 18:18:43 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIST_H
# define LIST_H

#include <stdlib.h>

typedef struct s_node
{
    void *value;
    struct s_node *next;
} t_node;

typedef struct s_gen_list
{
    t_node *head;
    size_t size;
} t_gen_list;


t_gen_list *init_list();
void insert_end(t_gen_list* list, void* value);
void destroy_gen_list(t_gen_list* list, void (value_destroyer)(void*));
# endif
