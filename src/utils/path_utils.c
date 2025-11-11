/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:26:13 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/09 20:29:26 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../external/libft/libft.h"
#include "../include/util.h"
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
char	**simple_split(char *arg, char c)
{
	size_t	i;
	char	**result;

	i = 0;
	if (!arg || !c)
		return (NULL);
	result = ft_calloc(3, sizeof(char *));
	while (arg[i])
	{
		if (arg[i] == c)
			break ;
		i++;
	}
	result[0] = ft_substr(arg, 0, i);
	if (arg[i] == c)
		result[1] = ft_substr(arg, i + 1, ft_strlen(arg) - i);
	return (result);
}
