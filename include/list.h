/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:41 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/25 15:17:43 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct s_node
{
	void			*value;
	struct s_node	*next;
}					t_node;

typedef struct s_gen_list
{
	t_node			*head;
	size_t			size;
}					t_gen_list;

t_gen_list			*init_list(void);
void				push_end(t_gen_list *list, void *value);
void				destroy_gen_list(t_gen_list *list,
						void(value_destroyer)(void *));
void				traverse(t_gen_list *list, void (*func)(void *));

#endif
