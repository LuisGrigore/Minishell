#include "../include/command.h"
#include "../include/util.h"
#include "../libft/libft.h"
#include "stdlib.h"
#include <stdio.h>

static void get_comman_type(t_command *command, char *cmd);
t_command *init_cmd()
{
    t_command *aux;

    aux = ft_caalloc(1, sizeof(t_command ));
    aux->cmd = NULL;
    aux->t_command_funct = NULL;
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
    clasification_redirections(new);
    get_comman_type(new, ft_split(new->cmd , ' ')[0]);
}

static void get_comman_type(t_command *command, char *cmd)
{
    size_t len;

    len = ft_strlen(cmd)-1;
    if(ft_strncmp(cmd, "cd", len) == 0)
        write(2,"Luis esto ya es tuyo\n",22);
    else if(ft_strncmp(cmd, "pwd", len) == 0)
        write(2,"Luis esto yaes tuyo\n",22);
    else if(ft_strncmp(cmd, "export", len) == 0)
        write(2,"Luis esto ya es tuyo\n",22);
    else if(ft_strncmp(cmd, "env", len) == 0)
        write(2,"Luis esto ya es tuyo\n",22);
    else if(ft_strncmp(cmd, "echo", len) == 0)
        write(2,"Luis esto ya es tuyo\n",22);
    else if(ft_strncmp(cmd, "exit", len) == 0)
        write(2,"Luis esto ya es tuyo\n",22);
    else
        write(2,"Luis esto ya es tuyo\n",22);
    printf("%s\n", command->cmd);

}

void cmd_assignation(char *cmd_line, t_command *head)
{
    char **cmd;
    int i;
    char    **aux;
    t_command *new_command;

    i = 0;
    cmd = ft_split2(cmd_line, '|');
    head->cmd = cmd[i];

    clasification_redirections(head);
    get_comman_type(head, ft_split(cmd[0], ' ')[0]);
    free_double_pointer(cmd);
    i++;
    while(cmd[i])
    {
        new_command = init_cmd();
        aux = ft_split(cmd[i], ' ');
        ft_add_fornt(cmd[i], head, new_command);
        free_double_pointer(aux);
        i++;
    }
    
    free(cmd);

}
void command_destroyer(t_command *cmd)
{
    t_command *aux;
    if(!cmd)
        return ;
    aux = NULL;
    while(cmd != NULL)
    {   
        aux = cmd;
        cmd = cmd->next;
        if(aux->cmd)
            free(aux->cmd);
        free(aux);
    }

}
t_command *lst_commad(t_command *cmds)
{
    t_command *aux;
    
    aux = cmds;
    while(aux->next != NULL)
       aux = aux->next;
    return(aux);
}

