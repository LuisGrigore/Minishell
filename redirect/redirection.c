/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:11:37 by dmaestro          #+#    #+#             */
/*   Updated: 2025/05/11 19:11:39 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/redirect.h"
#include "../libft/libft.h"
#include "../include/util.h"
#include "../include/command.h"
#include "../include/redirection_util.h"


static t_redirect *init_redirect();
static  e_redirect    which_type(char *str);
static void    get_the_file(t_command *cmd, char *c, t_redirect *redirect);
static  int    until_space(char *str);

void clasification_redirections(t_command *command)
{
    int i;
    t_redirect *aux2;
    t_redirect *aux;

    i = 0;
    aux2 = init_redirect();
    get_the_file(command, first_redirection(command->cmd), aux2);
    command->redirect  = aux2;
    while(first_redirection(command->cmd))
    {
        aux = init_redirect();
        get_the_file(command,first_redirection(command->cmd), aux);
        aux2->next = aux;
        aux2 = aux;
    }

}

static  t_redirect *init_redirect()
{
    t_redirect *aux;

    aux = ft_calloc(1 , sizeof(t_redirect *));

    aux->file = NULL;
    aux->redirect_simbol = NONE;
    aux->next = NULL;
    return(aux);
}

static void    get_the_file(t_command *cmd, char *c, t_redirect *redirect)
{
    int i;
    char *aux;
    size_t len;
    
    if(!c)
        return ;

    i = 0;
    len = ft_strlen(c);
    aux = cmd->cmd + special_char(cmd->cmd, c) + (int)len;
    while( aux[i] && ft_ispace(aux[i]) == 1 )
        aux[i]++;
    redirect->redirect_simbol = which_type(c);
    redirect->file = ft_substr(aux, i,until_space(aux + i));
    aux = ft_strdup(aux + i);
    free(cmd->cmd);
    cmd->cmd  = aux;
    return ;   
}

static  int    until_space(char *str)
{
    int result;

    result = 0;
    while(ft_ispace(str[result]) != 1 || str[result] != '\0')
        result++;
    return(result);
}

static  e_redirect    which_type(char *str)
{
    if(ft_strncmp(str, "<", 1) == 0)
        return LEFT_REDIRECT;
    if(ft_strncmp(str, ">", 1) == 0)
        return RIGHT_REDIRECT;
    if(ft_strncmp(str, ">>", 2) == 0)
        return DOUBLE_RIGHT_REDIRECT;
    if(ft_strncmp(str, "<<", 2) == 0)
        return DOUBLE_LEFT_REDIRECT;
    return ERROR;

}
