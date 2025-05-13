#ifndef COMMAND_H
# define COMMAND_H
# include "redirect.h"
# include "envioroment.h"
# include "command_functs.h"
#include "../include/list.h"


typedef struct s_command
{
    t_gen_list *args;
    t_gen_list   *redirects;
    t_command_funct command_funct;

}   t_command;

t_gen_list *get_command_list_from_line(char *line);
void destroy_command(t_command *cmd);

#endif