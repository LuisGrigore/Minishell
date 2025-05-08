#include "../include/command.h"
#include "../include/util.h"
#include "../libft/libft.h"
#include "stdlib.h"
#include <stdio.h>

t_command *init_cmd()
{
    t_command *aux;

    aux = ft_caalloc(1, sizeof(t_command ));
    aux->cmd = NULL;
    aux->cmd_type = NONE;
    aux->next = NULL;
    aux->redirect = NULL;
    return(aux);

}

int size_of_list(t_command *fst)
{
    int i;
    t_command *aux;

    aux = fst;
    i = 0;
    if(!fst)
        return(0);
    while(aux != NULL)
    {
        aux = aux->next;
        i++;
    }
    return(i);    

}

void ft_add_fornt(char *readed, t_command *fst, t_command *new)
{
    t_command *aux;

    aux = fst;
    if (!fst || !new)
        return ;
        
    while(aux->next != NULL)
        aux = aux->next;
    aux->next = new;
    if(readed)
        new->cmd = readed;
}

e_command_types get_comman_type(char *cmd_str)
{
    size_t len;
    len = ft_strlen(cmd_str)-1;
    if(ft_strncmp(cmd_str, "cd", len) == 0)
        return CD;
    else if(ft_strncmp(cmd_str, "pwd", len) == 0)
        return PWD;
    else if(ft_strncmp(cmd_str, "export", len) == 0)
        return EXPORT;
    else if(ft_strncmp(cmd_str, "env", len) == 0)
        return ENV;
    else if(ft_strncmp(cmd_str, "echo", len) == 0)
        return ECHOS;
    else if(ft_strncmp(cmd_str, "exit", len) == 0)
        return EXIT;
    else
        return BIN;
}

void cmd_assignation(char *cmds, t_command *head)
{
    char **cmd;
    int i;

    i = 0;
    cmd = ft_split2(cmds, '|');
    head->cmd = cmd[i];
    head->cmd_type = get_comman_type(ft_split(cmd[0], ' ')[0]);
    i++;
    while(cmd[i])
    {
        t_command *new_command = init_cmd();
        new_command->cmd_type = get_comman_type(ft_split(cmd[i], ' ')[0]);
        ft_add_fornt(cmd[i], head, new_command);
        i++;
    }
    free(cmd);

}

