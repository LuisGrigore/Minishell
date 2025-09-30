#include "../gen_link_list_internal.h"

void	*gen_list_find(t_gen_list *list, bool (*predicate)(void *))
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

void	*gen_list_find_ctx(t_gen_list *list,
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