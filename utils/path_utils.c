/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Path_Utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:26:13 by dmaestro          #+#    #+#             */
/*   Updated: 2025/05/05 18:26:15 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/util.h"
#include "../libft/libft.h"
#include "unistd.h"

int ft_ispace(char c)
{
	if(c ==  '\n' || c == ' ' || c == 9)
		return(1);
	return(0);
}
int special_char(char *str, char *c)
{
	int i;
	int b1;
	int b2;
	size_t len;

	if(!str || !c)
		return (9999);
	len = ft_strlen(c);
	i = 0;
	b1 = 0;
	b2 = 0;

	while (str[i])
	{
		if(str[i] == *"'" && b2 % 2 == 0)
			b1++;
		if(str[i] == '"' && b1 % 2 == 0)
			b2++;
		if(ft_strncmp(str + i, c, len)  == 0 && b1 % 2 == 0 && b2 % 2 == 0)
			return(i);
		i++;
	}
	return((int)len*34);
}