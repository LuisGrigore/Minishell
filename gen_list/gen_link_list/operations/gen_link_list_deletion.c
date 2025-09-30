#include "../gen_link_list_internal.h"

void	gen_list_remove_if(t_gen_list *list, bool (*predicate)(void *),
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

void	gen_list_remove_if_ctx(t_gen_list *list,
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