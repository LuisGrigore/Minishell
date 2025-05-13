/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:13:51 by dmaestro          #+#    #+#             */
/*   Updated: 2025/05/12 18:13:52 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/util.h"
#include "../include/redirection_util.h"
#include "unistd.h"
char *first_redirection(char *str)
{
    int l;
    int r;
    int dl;
    int dr;
    
    l = special_char(str, "<");
    r = special_char(str, ">");
    dl = special_char(str, "<<"); 
    dr = special_char(str, ">>") ;
    if(l < r && l < dl && l < dr)
        return ("<");
    if(r < l && r < dl && r < dr)
        return (">");
    if(dl < r && dl < l && dl < dr)
        return ("<<");
    if(dr < l && dr < dl && dr < r)
        return (">>");
    return(NULL);
}

