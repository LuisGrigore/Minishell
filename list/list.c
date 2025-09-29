/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:32:09 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/29 23:56:21 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "../libft/libft.h"
#include <stdlib.h>

t_gen_list	*init_list(void)
{
	t_gen_list	*list;

	list = malloc(sizeof(t_gen_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

void	push_end(t_gen_list *list, void *value)
{
	t_node	*node;

	if (!list)
		return ;
	node = malloc(sizeof(t_node));
	if (!node)
		return ;
	node->value = value;
	node->next = NULL;
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
}

void	push_front(t_gen_list *list, void *value)
{
	t_node	*node;

	if (!list)
		return ;
	node = malloc(sizeof(t_node));
	if (!node)
		return ;
	node->value = value;
	node->next = list->head;
	list->head = node;
	if (!list->tail)
		list->tail = node;
	list->size++;
}

void	*pop_front(t_gen_list *list)
{
	t_node	*node;
	void	*val;

	if (!list || !list->head)
		return (NULL);
	node = list->head;
	val = node->value;
	list->head = node->next;
	if (!list->head)
		list->tail = NULL;
	free(node);
	list->size--;
	return (val);
}

void	destroy_gen_list(t_gen_list *list, void(value_destroyer)(void *))
{
	t_node	*current;
	t_node	*tmp;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		tmp = current->next;
		if (value_destroyer)
			value_destroyer(current->value);
		free(current);
		current = tmp;
	}
	free(list);
}

void	traverse(t_gen_list *list, void (*func)(void *))
{
	t_node	*current;

	if (!list || !func)
		return ;
	current = list->head;
	while (current)
	{
		func(current->value);
		current = current->next;
	}
}

void	remove_if(t_gen_list *list, bool (*predicate)(void *),
		void (*value_destroyer)(void *))
{
	t_node	*current;
	t_node	*prev;
	t_node	*next;

	if (!list || !predicate)
		return ;
	current = list->head;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (predicate(current->value))
		{
			if (prev)
				prev->next = next;
			else
				list->head = next;
			if (current == list->tail)
				list->tail = prev;
			if (value_destroyer)
				value_destroyer(current->value);
			free(current);
			list->size--;
		}
		else
		{
			prev = current;
		}
		current = next;
	}
}

void	remove_if_ctx(t_gen_list *list,
			bool (*predicate)(void *element, void *context),
			void *context,
			void (*value_destroyer)(void *))
{
	t_node	*current;
	t_node	*prev;
	t_node	*next;

	if (!list || !predicate)
		return ;
	current = list->head;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (predicate(current->value, context))
		{
			if (prev)
				prev->next = next;
			else
				list->head = next;
			if (current == list->tail)
				list->tail = prev;
			if (value_destroyer)
				value_destroyer(current->value);
			free(current);
			list->size--;
		}
		else
		{
			prev = current;
		}
		current = next;
	}
}

void	*find_in_list(t_gen_list *list, bool (*predicate)(void *))
{
	t_node	*current;

	if (!list || !predicate)
		return (NULL);
	current = list->head;
	while (current)
	{
		if (predicate(current->value))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

t_iter	iter_start(t_gen_list *list)
{
	t_iter	it;

	it.current = list ? list->head : NULL;
	return (it);
}

void	*iter_next(t_iter *it)
{
	void	*val;

	if (!it || !it->current)
		return (NULL);
	val = it->current->value;
	it->current = it->current->next;
	return (val);
}

bool	contains_in_list(t_gen_list *list, bool (*predicate)(void *))
{
	return (find_in_list(list, predicate) != NULL);
}

void	*find_in_list_ctx(t_gen_list *list,
			bool (*predicate)(void *element, void *context),
			void *context)
{
	t_node *curr = list->head;

	while (curr)
	{
		if (predicate(curr->value, context))
			return curr->value;
		curr = curr->next;
	}
	return NULL;
}
bool	contains_in_list_ctx(t_gen_list *list,
			bool (*predicate)(void *element, void *context),
			void *context)
{
	return (find_in_list_ctx(list, predicate, context) != NULL);
}

/* Helper: get string length */
static size_t str_len(const char *s)
{
    size_t len = 0;
    while (s[len] != '\0')
        len++;
    return len;
}

/* Helper: copy src to dest at given position */
static void str_copy_at(char *dest, const char *src, size_t *pos)
{
    size_t i = 0;
    while (src[i] != '\0')
    {
        dest[*pos] = src[i];
        (*pos)++;
        i++;
    }
    dest[*pos] = '\0';
}

/* ============================================================
**  Serialization Implementations
** ============================================================
*/

/**
 * Convert a list into a single string in format: [elem1, elem2, ...]
 */
char *serialize_to_string(t_gen_list *list, t_element_to_string element_to_string)
{
    if (!list || !element_to_string)
        return NULL;

    // First, calculate total length needed
    size_t total_len = 2; // '[' + ']'
    t_node *current = list->head;
    size_t count = 0;

    while (current)
    {
        char *elem_str = element_to_string(current->value);
        if (!elem_str)
            return NULL;

        total_len += str_len(elem_str);
        if (current->next)
            total_len += 2; // for ", "

        free(elem_str);
        current = current->next;
        count++;
    }

    char *result = malloc(total_len + 1); // +1 for '\0'
    if (!result)
        return NULL;

    size_t pos = 0;
    result[pos++] = '[';
    result[pos] = '\0';

    current = list->head;
    size_t i = 0;
    while (current)
    {
        char *elem_str = element_to_string(current->value);
        if (!elem_str)
        {
            free(result);
            return NULL;
        }

        str_copy_at(result, elem_str, &pos);
        free(elem_str);

        if (current->next)
        {
            result[pos++] = ',';
            result[pos++] = ' ';
            result[pos] = '\0';
        }

        current = current->next;
        i++;
    }

    result[pos++] = ']';
    result[pos] = '\0';

    return result;
}

/**
 * Convert a list into an array of strings. Each element is a string returned by element_to_string.
 * The array is null-terminated.
 */
char **serialize_to_string_array(t_gen_list *list, t_element_to_string element_to_string)
{
    if (!list || !element_to_string)
        return NULL;

    char **array = malloc((list->size + 1) * sizeof(char *));
    if (!array)
        return NULL;

    t_node *current = list->head;
    size_t i = 0;

    while (current)
    {
        array[i] = element_to_string(current->value);
        if (!array[i])
        {
            for (size_t j = 0; j < i; j++)
                free(array[j]);
            free(array);
            return NULL;
        }
        i++;
        current = current->next;
    }

    array[i] = NULL; // Null-terminate
    return array;
}

/**
 * Convert a null-terminated array of strings into a generic linked list.
 *
 * @param array Null-terminated array of strings.
 * @param string_to_element Function to convert each string into a list element.
 * @return Pointer to a newly allocated list, or NULL on error.
 */
t_gen_list *deserialize_from_string_array(char **array, t_string_to_element string_to_element)
{
    if (!array || !string_to_element)
        return NULL;

    t_gen_list *list = (t_gen_list *)malloc(sizeof(t_gen_list));
    if (!list) return NULL;

    list->head = NULL;
    list->size = 0;
    t_node *last = NULL;

    for (size_t i = 0; array[i] != NULL; i++) {
        void *value = string_to_element(array[i]);
        if (!value) goto error_cleanup;

        t_node *node = (t_node *)malloc(sizeof(t_node));
        if (!node) {
            free(value);
            goto error_cleanup;
        }
        node->value = value;
        node->next = NULL;

        if (!list->head)
            list->head = node;
        else
            last->next = node;
        last = node;
        list->size++;
    }

    return list;

error_cleanup:
    t_node *tmp = list->head;
    while (tmp) {
        t_node *next = tmp->next;
        free(tmp->value);
        free(tmp);
        tmp = next;
    }
    free(list);
    return NULL;
}