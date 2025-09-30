#include "../gen_link_list_internal.h"

bool gen_list_is_empty(t_gen_list *list)
{
	return (list->size == 0);
}

bool	gen_list_has(t_gen_list *list, bool (*predicate)(void *))
{
	return (gen_list_find(list, predicate) != NULL);
}


bool	gen_list_has_ctx(t_gen_list *list,
			bool (*predicate)(void *element, void *context),
			void *context)
{
	return (gen_list_find_ctx(list, predicate, context) != NULL);
}