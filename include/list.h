
#include <stdlib.h>

typedef struct s_node
{
    void *value;
    s_node *next;
} t_node;

typedef struct s_list
{
    t_node *first;
    size_t size;

} t_list;


t_list init_list();
void destroy_list();