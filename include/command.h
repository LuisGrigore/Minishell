#ifndef COMMAND_H
# define COMMAND_H
# include "redirect.h"
# include "command_specific.h"

typedef struct s_comand
{
    t_bin_cmd *bin;
    t_builtin_cmd *builtin;
    t_redirect    *redirect;
    char *cmd;
    struct s_comand *next;
}   t_comand;

t_comand *init_cmd();
int size_of_list(t_comand *fst);
void ft_add_fornt(char *readed, t_comand *fst, t_comand *new_command);
void cmd_assignation(char *cmds, t_comand *head);



#endif