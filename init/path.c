/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:38:04 by dmaestro          #+#    #+#             */
/*   Updated: 2025/05/03 19:38:09 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/util.h"

static char *history_checker(char *cmd);
char *check_cmd(char *cmd)
{
    int i;
    int b;

    b = 0;
    i = 0;
    if(history_checker(cmd) == NULL)
        return(NULL);
    while (cmd[i])
    {
        if (cmd [i] == '"' )
            b = 1;
        i++;
        while (cmd[i] && b == 1)
        {
            if(cmd[i] == '"')
                b = 0;
            i++;
        }   
    }
    if(b != 0)
    {
        add_history(cmd);
        return(NULL);
    }
    return(cmd);
}
static char *history_checker(char *cmd)
{
    int i;

    i = 0;
    if(cmd[0] == '|' || cmd[ft_strlen(cmd)] == '|')
     {
        add_history(cmd);
        return(NULL);
     }

     while(cmd[i])
     {
        if(ft_ispace(cmd[i]) == 0)
                break;
        i++;
     }
     if(cmd[i] == '\0')
        return(NULL);
     return(cmd);
}
