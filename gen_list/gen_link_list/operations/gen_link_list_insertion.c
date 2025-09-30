#include "../gen_link_list_internal.h"

void	gen_list_push_back(t_gen_list *list, void *value)
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

void	gen_list_push_front(t_gen_list *list, void *value)
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