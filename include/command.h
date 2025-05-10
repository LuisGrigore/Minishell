#ifndef COMMAND_H
# define COMMAND_H
# include "redirect.h"

typedef enum e_command_types
{
    NONE,
    BIN,
    CD,
    ENV,
    EXPORT,
    PWD,
    ECHOS,
    EXIT,

    
} e_command_types;

typedef struct s_command
{
    char *cmd;
    t_redirect    *redirect;
    e_command_types cmd_type;
    struct s_command *next;
}   t_command;

t_command *init_cmd();
int size_of_list(t_command *fst);
void ft_add_fornt(char *readed, t_command *fst, t_command *new_command);
void cmd_assignation(char *cmds, t_command *head);
void exec(t_command command);
void command_destroyer(t_command *cmd);
t_command *lst_commad(t_command *cmds);


#endif