/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:30:11 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/10 17:49:57 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_LIST_H
# define GEN_LIST_H
# include <stdbool.h>
# include <stdlib.h>

/* ============================================================
**  Status Codes
** ============================================================
*/

typedef enum e_gen_list_status_code
{
	GEN_LIST_OK,
	GEN_LIST_MALLOC_ERR,
	GEN_LIST_IS_NULL_ERR,
} t_gen_list_status_code;

/* ============================================================
**  Data Structures
** ============================================================
*/

/**
 * @brief Generic list.
 *
 * Contains pointers to the head and tail nodes and a size counter.
 *
 * @see t_gen_list_iter
 */
typedef struct s_gen_list		t_gen_list;

/**
 * @brief Iterator for a generic list.
 *
 * Maintains the current node during iteration.
 *
 * @see t_gen_list
 */
typedef struct s_gen_list_iter	t_gen_list_iter;

/* ============================================================
**  Function Pointer Typedefs
** ============================================================
*/

/**
 * @brief Function that converts a list element into a string.
 *
 * @param element Pointer to the element to convert.
 * @return Dynamically allocated string representing the element.
 */
typedef char					*(*t_element_to_string)(void *element);

/**
 * @brief Function that frees or destroys a value stored in the list.
 *
 * @param element Pointer to the element to destroy.
 */
typedef void					(*t_element_destroyer)(void *element);

/**
 * @brief Predicate function used to test list elements.
 *
 * @param element Pointer to the element to test.
 * @return true if the element satisfies the condition, false otherwise.
 */
typedef bool					(*t_predicate)(void *element);

/**
 * @brief Predicate function with user-defined context.
 *
 * @param element Pointer to the element to test.
 * @param context Pointer to extra data required by the predicate.
 * @return true if the element satisfies the condition, false otherwise.
 */
typedef bool					(*t_predicate_ctx)(void *element,
						void *context);

/**
 * @brief Function applied to each list element during traversal.
 *
 * @param element Pointer to the element to process.
 */
typedef void					(*t_apply_func)(void *element);

/**
 * @brief Function applied to each list element during traversal, with context.
 *
 * @param element Pointer to the element to process.
 * @param context Extra pointer passed to the function.
 *
 * @see t_apply_func
 */
typedef void					(*t_apply_func_ctx)(void *element,
						void *context);

/**
 * @brief Function that converts a string into a list element.
 *
 * @param str Null-terminated string to convert.
 * @return Dynamically allocated element, or NULL on failure.
 */
typedef void					*(*t_string_to_element)(const char *str);

/* ============================================================ **
** Life Cycle
** ============================================================ */
/**
 * @brief Initialize an empty list.
 *
 * @return Pointer to the created list, or NULL if allocation fails.
 */
t_gen_list						*gen_list_create(void);

/**
 * @brief Destroy the entire list and its nodes.
 *
 * @param list List to destroy.
 * @param element_destroyer Function to free each stored value, can be NULL.
 * @see t_element_destroyer
 */
void							gen_list_destroy(t_gen_list *list,
									t_element_destroyer element_destroyer);

/* ============================================================ **
** Operations
** ============================================================ */
/**
 * @brief Insert a value at the end of the list.
 *
 * @param list List where the value will be inserted.
 * @param value Pointer to the value to insert.
 */
t_gen_list_status_code							gen_list_push_back(t_gen_list *list,
									void *value);

/**
 * @brief Insert a value at the beginning of the list.
 *
 * @param list List where the value will be inserted.
 * @param value Pointer to the value to insert.
 */
t_gen_list_status_code							gen_list_push_front(t_gen_list *list,
									void *value);

/**
 * @brief Remove the first node of the list and return its value.
 *
 * @param list List from which to remove the first node.
 * @return Value stored in the first node, or NULL if the list is empty.
 */
void							*gen_list_pop_front(t_gen_list *list);

/**
 * @brief Remove the last node of the list and return its value.
 *
 * @param list List from which to remove the last node.
 * @return Value stored in the last node, or NULL if the list is empty.
 */
void	*gen_list_pop_back(t_gen_list *list);

/**
* @brief Remove nodes that satisfy a predicate.
*
* @param list List to modify.
* @param predicate Predicate function to decide which nodes to remove.
* @param element_destroyer Function to free the value of each removed node,
can be NULL.
* @see t_predicate
* @see t_element_destroyer
*/
t_gen_list_status_code							gen_list_remove_if(t_gen_list *list,
									t_predicate predicate,
									t_element_destroyer element_destroyer);

/**
* @brief Remove nodes that satisfy a predicate with context.
*
* @param list List to modify.
* @param predicate Predicate function that takes (element, context).
* @param context Extra pointer passed to the predicate on each call.
* @param element_destroyer Function to free the value of each removed node,
can be NULL.
* @see t_predicate_ctx
* @see t_element_destroyer
*/
t_gen_list_status_code							gen_list_remove_if_ctx(t_gen_list *list,
									t_predicate_ctx predicate, void *context,
									t_element_destroyer element_destroyer);

/* ============================================================ **
** Queries
** ============================================================ */
/**
 * @brief Apply a function to all elements of the list.
 *
 * @param list List to traverse.
 * @param func Function to apply to each value.
 * @see t_apply_func
 * @see gen_list_for_each_ctx
 */
t_gen_list_status_code							gen_list_for_each(t_gen_list *list,
									t_apply_func func);

/**
 * @brief Apply a function to all elements of the list, with context.
 *
 * @param list List to traverse.
 * @param func Function to apply to each value with context.
 * @param context Extra pointer passed to the function on each call.
 * @see t_apply_func_ctx
 * @see gen_list_for_each
 */
t_gen_list_status_code							gen_list_for_each_ctx(t_gen_list *list,
									t_apply_func_ctx func, void *context);

//TODO :: Crear un for each que tome una funcion que devuelva un estado de error y que tome el estado de exito para que tambien pueda gestionarse los errores
									
/**
 * @brief Find the first element that satisfies a predicate.
 *
 * @param list List to search.
 * @param predicate Predicate function to test each element.
 * @return Value of the first matching node, or NULL if none found.
 * @see t_predicate
 */
void							*gen_list_find(t_gen_list *list,
									t_predicate predicate);

/**
 * @brief Find the first element that satisfies a predicate with context.
 *
 * @param list List to search.
 * @param predicate Predicate function that takes (element, context).
 * @param context Context pointer passed to the predicate.
 * @return Value of the first matching node, or NULL if none found.
 * @see t_predicate_ctx
 */
void							*gen_list_find_ctx(t_gen_list *list,
									t_predicate_ctx predicate, void *context);

/**
 * @brief Gets the current size of the list.
 *
 * @param list List to search.
 * @return list size.
 * @see t_gen_list
 */
size_t							gen_list_get_size(t_gen_list *list);

void							*gen_list_peek_top(t_gen_list *list);
void *gen_list_peek_bottom(t_gen_list *list);
void							*gen_list_peek_index(t_gen_list *list, int idx);

/**
 * @brief Check if the list contains an element that satisfies a predicate.
 *
 * @param list List to search.
 * @param predicate Predicate function to test elements.
 * @return true if a matching element is found, false otherwise.
 * @see t_predicate
 */
bool							gen_list_has(t_gen_list *list,
									t_predicate predicate);

/**

* @brief Check if the list contains an element that satisfies a predicate.
*
* @param list List to search.
* @param predicate Predicate function that takes (element, context).
* @param context Context pointer passed to the predicate.
* @return true if a matching element is found, false otherwise.
* @see t_predicate_ctx
*/
bool							gen_list_has_ctx(t_gen_list *list,
									t_predicate_ctx predicate, void *context);

/**
 * @brief Check if the list is empty.
 *
 * @param list List to search.
 * @return true if is empty, false otherwise.
 * @see t_gen_list
 */
bool							gen_list_is_empty(t_gen_list *list);

/* ============================================================ **
** Iteration
** ============================================================ */
/**
 * @brief Initialize an iterator at the start of the list.
 *
 * @param list List to iterate.
 * @return Iterator pointing to the first node.
 * @see t_gen_list_iter
 */
t_gen_list_iter					*gen_list_iter_start(t_gen_list *list);

/**
 * @brief Get the next value from the list using the iterator and advance it.
 *
 * @param it Iterator of the list.
 * @return Value of the current node, or NULL if the end is reached.
 * @see t_gen_list_iter
 */
void							*gen_list_iter_next(t_gen_list_iter *it);

/**
 * @brief Destroys allocated iterator
 *
 * @param it Iterator of the list.
 * @see t_gen_list_iter
 */
void							gen_list_iter_destroy(t_gen_list_iter *it);

/* ============================================================ **
** Serialization
** ============================================================ */
/**
 * @brief Convert a generic list into a single string representation.
 *
 * @param list Pointer to the list to serialize.
 * @param element_to_string Function that converts each element to a string.
 * @return Dynamically allocated string representing the list.
 * @see t_element_to_string
 */
char							*gen_list_serialize_to_string(t_gen_list *list,
									t_element_to_string element_to_string);

/**
* @brief Convert a generic list into an array of strings.
*
* @param list Pointer to the list to serialize.
* @param element_to_string Function that converts each element to a string.
* @return Dynamically allocated null-terminated array of strings,
one per element.
* @see t_element_to_string
*/
char							**gen_list_serialize_to_string_array(t_gen_list *list,
									t_element_to_string element_to_string);

/**
 * @brief Convert a null-terminated array of strings into a generic list.
 *
 * @param array Null-terminated array of strings.
 * @param string_to_element Function to convert each string into a list element.
 * @return Pointer to a newly allocated list, or NULL on error.
 * @see t_string_to_element
 */
t_gen_list						*gen_list_deserialize_from_string_array(char **array,
									t_string_to_element string_to_element);

#endif
