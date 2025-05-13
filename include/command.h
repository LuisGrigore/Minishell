#ifndef COMMAND_H
# define COMMAND_H
# include "redirect.h"
# include "envioroment.h"
# include "command_functs.h"

typedef struct s_command
{
    char *cmd;
    t_redirect    *redirect;
    t_command_funct;
    struct s_command *next;
}   t_command;

t_command *init_cmd();
int size_of_list(t_command *fst);
void ft_add_fornt(char *readed, t_command *fst, t_command *new_command);
void cmd_assignation(char *cmds, t_command *head);
void command_destroyer(t_command *cmd);
t_command *lst_commad(t_command *cmds); 
void clasification_redirections(t_command *command);

#endif