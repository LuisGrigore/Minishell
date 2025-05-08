/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:56:27 by dmaestro          #+#    #+#             */
/*   Updated: 2025/05/03 19:56:29 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"


int main(int args, char **argv, char **env)
{
    t_comand *cmd;
    t_comand *aux;
    char *recept;
    char *name;

    name = username(env);
    cmd = init_cmd();
    printf("%s\n", argv[args]);
    
    while(1)
    {
        recept = readline(name);
        if(check_cmd(recept) == NULL)
            continue ;
        add_history(recept);
        cmd_assignation(recept, cmd);
        aux = cmd;
        while(aux != NULL)
        {
            printf("%s\n", aux->cmd);
            aux = aux->next;
        }
    }

}
