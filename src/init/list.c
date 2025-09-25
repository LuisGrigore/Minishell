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

void	insert_end(t_gen_list *list, void *value)
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

t_node	*get_last_node_of_list(t_gen_list *list)
{
	t_node	*current_node;

	if (!list || !list->head)
		return (NULL);
	current_node = list->head;
	while (current_node->next != NULL)
		current_node = current_node->next;
	return (current_node);
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

void	*unlink_element_from_list(t_gen_list *list, void *element_to_return)
{
	t_node	*current_node;
	t_node	*aux_node;

	current_node = list->head;
	while (current_node->next != NULL)
	{
		if (current_node->value == element_to_return)
			break ;
		aux_node = current_node;
	}
	if (!aux_node)
		list->head = current_node->next;
	else
		aux_node->next = current_node->next;
	free(current_node);
	return (element_to_return);
}
