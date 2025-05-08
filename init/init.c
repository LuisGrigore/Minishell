/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:09:38 by dmaestro          #+#    #+#             */
/*   Updated: 2025/05/03 20:09:40 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

char *username(char **env)
{
    int i;

    if(!env)
        return(ft_strdup("minishell%"));
    i = 0;
    while(env[i])
    {
        if(ft_strncmp(env[i], "LOGNAME=", 8) == 0)
            return(ft_strjoin(ft_strdup(env[i] + 8), "%>$"));
        i++;
    }
    return(ft_strdup("minishell%"));
}


