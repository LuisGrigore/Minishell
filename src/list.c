#include "../include/list.h"
#include "../libft/libft.h"
#include <stdlib.h>

t_gen_list	*init_list(void)
{
	t_gen_list	*new_list;

	new_list = ft_calloc(1, sizeof(t_list));
	new_list->head = NULL;
	new_list->size = 0;
	return (new_list);
}

void	push_end(t_gen_list *list, void *value)
{
	t_node	*new_node;
	t_node	*current;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	new_node->value = value;
	new_node->next = NULL;
	if (list->head == NULL)
		list->head = new_node;
	else
	{
		current = list->head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
	list->size++;
}

void	destroy_gen_list(t_gen_list *list, void (*value_destroyer)(void *))
{
	t_node	*current;
	t_node	*next;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		next = current->next;
		if (value_destroyer)
		{
			value_destroyer(current->value);
		}
		free(current);
		current = next;
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
