#include "../include/command.h"
#include "../include/util.h"
#include "../libft/libft.h"
#include "stdlib.h"

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

void cmd_assignation(char *cmds, t_command *head)
{
    char **cmd;
    int i;

    i = 0;
    cmd = ft_split2(cmds, '|');
    head->cmd = cmd[i];
    i++;
    while(cmd[i])
    {
        ft_add_fornt(cmd[i], head, init_cmd());
        i++;
    }
    free(cmd);

}

