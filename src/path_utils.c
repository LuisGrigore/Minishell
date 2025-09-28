/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:26:13 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/28 17:55:49 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/util.h"
#include "../libft/libft.h"
#include "unistd.h"

int	ft_ispace(char c)
{
	if (c == '\n' || c == ' ' || c == '\t')
		return (1);
	return (0);
}
int	special_char(char *str, char *c)
{
	int		i;
	int		b1;
	int		b2;
	size_t	len;

	if (!str || !c)
		return ((int)ft_strlen(str) + 1);
	len = ft_strlen(c);
	i = 0;
	b1 = 0;
	b2 = 0;
	while (str[i])
	{
		if (str[i] == *"'" && b2 % 2 == 0)
			b1++;
		if (str[i] == '"' && b1 % 2 == 0)
			b2++;
		if (ft_strncmp(str + i, c, len) == 0 && b1 % 2 == 0 && b2 % 2 == 0)
			return (i);
		i++;
	}
	return ((int)ft_strlen(str) + 1);
}

char	*get_next_argument(char *c, char *str)
{
	int		i;
	size_t	len;

	len = ft_strlen(c);
	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str, c, len))
			break ;
		i++;
	}
	return (str + i + (int)len);
}
