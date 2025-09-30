/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 05:05:04 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/30 14:41:51 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_LINK_LIST_INTERNAL_H
# define GEN_LINK_LIST_INTERNAL_H

# include <stdlib.h>
#include <stdlib.h>
#include "../libft/libft.h"
# include "../gen_list.h"

/**
 * @brief Node of a generic singly linked list.
 *
 * Each node stores a generic value and a pointer to the next node.
 *
 * @see t_gen_list
 * @see t_gen_list_iter
 */
typedef struct s_node
{
	void			*value;
	struct s_node	*next;
}					t_node;

/**
 * @brief Generic singly linked list container.
 *
 * Holds pointers to the first and last nodes,
 * as well as the total number of stored elements.
 *
 * @see t_node
 * @see t_gen_list_iter
 */
struct s_gen_list
{
	t_node			*head;
	t_node			*tail;
	size_t			size;
};

/**
 * @brief Iterator for traversing a generic linked list.
 *
 * Stores the current node and is advanced
 * with @ref gen_list_iter_next.
 *
 * @see t_node
 * @see t_gen_list
 */
struct s_gen_list_iter
{
	t_node			*current;
};

#endif
