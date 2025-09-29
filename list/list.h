/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:30:11 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/29 23:56:21 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include <stdbool.h>
# include <stdlib.h>

/* ============================================================
**  Data Structures
** ============================================================
*/

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
**  Function Pointer Typedefs
** ============================================================
*/

/**
 * @brief Function that converts a list element into a string.
 *
 * @param element Pointer to the element to convert.
 * @return A dynamically allocated string representation of the element.
 */
typedef char *(*t_element_to_string)(void *element);

/**
 * @brief Function that frees or destroys a value stored in the list.
 *
 * @param element Pointer to the element to destroy.
 */
typedef void (*t_value_destroyer)(void *element);

/**
 * @brief Predicate function used to test list elements.
 *
 * @param element Pointer to the element to test.
 * @return true if the element satisfies the condition, false otherwise.
 */
typedef bool (*t_predicate)(void *element);

/**
 * @brief Predicate function with context.
 *
 * @param element Pointer to the element to test.
 * @param context Pointer to extra data required by the predicate.
 * @return true if the element satisfies the condition, false otherwise.
 */
typedef bool (*t_predicate_ctx)(void *element, void *context);

/**
 * @brief Function applied to each list element during traversal.
 *
 * @param element Pointer to the element to process.
 */
typedef void (*t_apply_func)(void *element);

/**
 * @brief Function that converts a string into a list element.
 *
 * @param str Null-terminated string to convert.
 * @return A dynamically allocated element, or NULL on failure.
 */
typedef void *(*t_string_to_element)(const char *str);

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
void				destroy_gen_list(t_gen_list *list, t_value_destroyer value_destroyer);

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
 * @param predicate Predicate function to decide which nodes to remove.
 * @param value_destroyer Function to free the value of each removed node.
 */
void				remove_if(t_gen_list *list, t_predicate predicate, t_value_destroyer value_destroyer);

/**
 * @brief Remove nodes from the list that satisfy a condition with context.
 *
 * @param list List to modify.
 * @param predicate Predicate function that takes (element, context).
 * @param context Extra pointer passed to the predicate on each call.
 * @param value_destroyer Function to free the value of each removed node, can be NULL.
 */
void				remove_if_ctx(t_gen_list *list, t_predicate_ctx predicate, void *context, t_value_destroyer value_destroyer);

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
void				traverse(t_gen_list *list, t_apply_func func);

/**
 * @brief Find the first element that satisfies a predicate.
 *
 * @param list List to search.
 * @param predicate Predicate function to test each element.
 * @return Value of the first node that satisfies the condition, or NULL if none found.
 */
void				*find_in_list(t_gen_list *list, t_predicate predicate);

/**
 * @brief Find the first element in the list that satisfies a predicate with context.
 *
 * @param list List to search.
 * @param predicate Predicate function that takes (element, context).
 * @param context Context pointer passed to the predicate.
 * @return Value of the first matching node, or NULL if none found.
 */
void				*find_in_list_ctx(t_gen_list *list, t_predicate_ctx predicate, void *context);

/**
 * @brief Check if the list contains an element that satisfies a predicate.
 *
 * @param list List to search.
 * @param predicate Predicate function to test elements.
 * @return true if a matching element is found, false otherwise.
 */
bool				contains_in_list(t_gen_list *list, t_predicate predicate);

/**
 * @brief Check if the list contains an element that satisfies a predicate with context.
 *
 * @param list List to search.
 * @param predicate Predicate function that takes (element, context).
 * @param context Context pointer passed to the predicate.
 * @return true if a matching element is found, false otherwise.
 */
bool				contains_in_list_ctx(t_gen_list *list, t_predicate_ctx predicate, void *context);

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

/* ============================================================
**  Serialization
** ============================================================
*/

/**
 * @brief Convert a generic list into a single string representation.
 *
 * @param list Pointer to the list to serialize.
 * @param element_to_string Function that converts each element to a string.
 * @return Dynamically allocated string representing the list.
 */
char				*serialize_to_string(t_gen_list *list, t_element_to_string element_to_string);

/**
 * @brief Convert a generic list into an array of strings.
 *
 * @param list Pointer to the list to serialize.
 * @param element_to_string Function that converts each element to a string.
 * @return Dynamically allocated null-terminated array of strings, one per element.
 */
char				**serialize_to_string_array(t_gen_list *list, t_element_to_string element_to_string);

/* ============================================================
**  Deserialization
** ============================================================
*/
/**
 * Convert a null-terminated array of strings into a generic linked list.
 *
 * @param array Null-terminated array of strings.
 * @param string_to_element Function to convert each string into a list element.
 * @return Pointer to a newly allocated list, or NULL on error.
 */
t_gen_list *deserialize_from_string_array(char **array, t_string_to_element string_to_element);

#endif