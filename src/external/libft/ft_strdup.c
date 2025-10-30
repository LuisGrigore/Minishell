/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:58:43 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/28 16:41:54 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *str, char *dest)
{
	int	i;

	i = 0;
	if(!str || !dest)
		return (NULL);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*p1;

	if(!s)
		return (NULL);
	p1 = malloc(ft_strlen(s) + 1);
	if (!p1)
		return (NULL);
	ft_strcpy((char *)s, p1);
	return (p1);
}
