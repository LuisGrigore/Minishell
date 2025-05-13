#include "../include/redirect.h"
#include "../libft/libft.h"

t_gen_list *get_redirects_from_str_arr(char *str)
{
    t_gen_list *redirects = init_list();
    int i = 0;
    while (str[i])
    {
        if(command_line[i] != "<" && command_line[i] != "<<" && command_line[i] != ">" && command_line[i] != ">>")
    }
}