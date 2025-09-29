/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:32:09 by lgrigore          #+#    #+#             */
/*   Updated: 2025/09/29 16:13:27 by lgrigore         ###   ########.fr       */
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