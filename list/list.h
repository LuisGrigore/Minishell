/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:39:48 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/29 16:28:00 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_node
{
	void			*value;
	struct s_node	*next;
}					t_node;

typedef struct s_gen_list
{
	t_node			*head;
	t_node			*tail;
	size_t			size;
}					t_gen_list;

typedef struct s_iter
{
	t_node			*current;
}					t_iter;

/* ============================================================
**  Initialization and Destruction
** ============================================================
*/

/**
 * @brief Initialize an empty list.
 *
 * @return Pointer to the created list, or NULL if allocation fails.
 */
t_gen_list			*init_list(void);

/**
 * @brief Destroy the entire list and its nodes.
 *
 * @param list List to destroy.
 * @param value_destroyer Function to free each stored value, can be NULL.
 */
void				destroy_gen_list(t_gen_list *list,
						void(value_destroyer)(void *));

/* ============================================================
**  Insertion and Removal
** ============================================================
*/

/**
 * @brief Insert a value at the end of the list (O(1)).
 *
 * @param list List where the value will be inserted.
 * @param value Pointer to the value to insert.
 */
void				push_end(t_gen_list *list, void *value);

/**
 * @brief Insert a value at the beginning of the list (O(1)).
 *
 * @param list List where the value will be inserted.
 * @param value Pointer to the value to insert.
 */
void				push_front(t_gen_list *list, void *value);

/**
 * @brief Remove the first node of the list and return its value.
 *
 * @param list List from which to remove the first node.
 * @return Value stored in the first node, or NULL if the list is empty.
 */
void				*pop_front(t_gen_list *list);

/**
 * @brief Remove nodes from the list that satisfy a condition.
 *
 * @param list List to modify.
 * @param predicate Function that returns true if the node must be removed.
 * @param value_destroyer Function to free the value of each removed node.
 */
void				remove_if(t_gen_list *list, bool (*predicate)(void *),
						void (*value_destroyer)(void *));
/**
 * @brief Remove nodes from the list that satisfy a condition with context.
 *
 * @param list List to modify.
 * @param predicate Function that takes (element, context) and returns true if
 *                  the node must be removed.
 * @param context Extra pointer passed to the predicate on each call.
 * @param value_destroyer Function to free the value of each removed node,
 *                        can be NULL.
 */
void	remove_if_ctx(t_gen_list *list,
			bool (*predicate)(void *element, void *context),
			void *context,
			void (*value_destroyer)(void *));

/* ============================================================
**  Traversal and Search
** ============================================================
*/

/**
 * @brief Traverse all elements of the list and apply a function to each value.
 *
 * @param list List to traverse.
 * @param func Function to apply to each value.
 */
void				traverse(t_gen_list *list, void (*func)(void *));

/**
 * @brief Find the first element that satisfies a condition.
 *
 * @param list List to search.
 * @param predicate Function that returns true if the value satisfies the condition.
 * @return Value of the first node that satisfies the condition,
 *         or NULL if no match is found.
 */
void				*find_in_list(t_gen_list *list, bool (*predicate)(void *));
/**
 * @brief Find the first element in the list that matches a target value.
 *
 * @param list List to search.
 * @param predicate Function that compares an element with the target.
 *                   Returns true if they match.
 * @param context Context for predicate.
 * @return The value of the first matching node, or NULL if no match is found.
 */
void				*find_in_list_ctx(t_gen_list *list, bool (*predicate)(void *element, void *context),
					void *context);

/**
 * @brief Check if the list contains an element that satisfies a condition.
 *
 * This function internally uses `find_in_list` to traverse the list
 * and check if there is at least one node whose value matches.
 *
 * @param list List to search.
 * @param predicate Function that returns true if the value satisfies the condition.
 * @return true if a matching value is found, false otherwise.
 */
bool				contains_in_list(t_gen_list *list, bool (*predicate)(void *));
/**
 * @brief Check if the list contains a value that matches a target.
 *
 * @param list List to search.
 * @param predicate Function that compares an element with the target.
 *                   Returns true if they match.
 * @param context Target value to compare against.
 * @return true if a match is found, false otherwise.
 */
bool	contains_in_list_ctx(t_gen_list *list,
			bool (*predicate)(void *element, void *context),
			void *context);


/* ============================================================
**  Iteration
** ============================================================
*/

/**
 * @brief Initialize an iterator at the start of the list.
 *
 * @param list List to iterate.
 * @return Iterator pointing to the first node.
 */
t_iter				iter_start(t_gen_list *list);

/**
 * @brief Get the next value from the list using the iterator and advance it.
 *
 * @param it Iterator of the list.
 * @return Value of the current node and advances, or NULL if the end is reached.
 */
void				*iter_next(t_iter *it);

#endif
