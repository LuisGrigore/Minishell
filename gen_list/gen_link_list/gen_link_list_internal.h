/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 05:05:04 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/01 00:32:01 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_LINK_LIST_INTERNAL_H
# define GEN_LINK_LIST_INTERNAL_H

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
struct				s_gen_list
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
struct				s_gen_list_iter
{
	t_node			*current;
};

/**
 * @brief Returns the length of a null-terminated string.
 *
 * @param s Pointer to the input string.
 * @return Number of characters before the null terminator.
 */
size_t				str_len(const char *s);

/**
 * @brief Copies a string into dest at a given position.
 *
 * Appends src into dest starting at *pos, updates *pos,
 * and null-terminates the result.
 *
 * @param dest Destination buffer.
 * @param src  Source string.
 * @param pos  Pointer to current write position in dest.
 */
void				str_copy_at(char *dest, const char *src, size_t *pos);

#endif
