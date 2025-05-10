/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envioroment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:35:48 by dmaestro          #+#    #+#             */
/*   Updated: 2025/05/10 17:35:50 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/envioroment.h"
#include "../libft/libft.h"
#include "stdlib.h"
#include <stdio.h>

t_envioroment *init_env()
{
    t_envioroment *aux;

    aux = NULL;
    aux = ft_calloc(1, sizeof(t_envioroment));
    aux->path = NULL;
    aux->next = NULL;
    return(aux);
}
void env_to_list(char **env, t_envioroment *envioroment)
{
    int i;
    t_envioroment *aux;
    t_envioroment *aux2;
    aux = envioroment;
    i = 1;
    envioroment->path = ft_strdup(env[i]);
    while(env[i])
    {
        aux2 = init_env();
        aux->next = aux2;
        aux2->path = ft_strdup(env[i]);
        aux = aux2;
        i++;
    }
}
char **env_to_dbarray(t_envioroment *envioroment)
{
    char **result;
    int i;
    t_envioroment *aux;

    result = NULL;
    if(!envioroment)
        return(NULL);
    result = ft_caalloc(size_of_env(envioroment) + 1, sizeof(char *));
    i = 0;
    aux = envioroment;
    while(aux != NULL)
    {
        result[i] = aux->path;
        i++;
        aux = aux->next;
    }
    env_destroyer(envioroment);
    return(result);
}
int size_of_env(t_envioroment *fst)
{
    int i;
    t_envioroment *aux;

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
void env_destroyer(t_envioroment *fst)
{
    t_envioroment *aux;
    if(!fst)
        return ;
    aux = NULL;
    while(fst != NULL)
    {   
        aux = fst;
        fst = fst->next;
        free(aux);
    }
}

