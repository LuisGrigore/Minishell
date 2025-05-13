
#include <stdlib.h>

typedef struct s_node
{
    void *value;
    struct s_node *next;
} t_node;

typedef struct s_gen_list
{
    t_node *head;
    size_t size;
} t_gen_list;


t_gen_list *init_list();
void insert_end(t_gen_list* list, void* value);
void destroy_gen_list(t_gen_list* list, void (*value_destroyer)(void*));
