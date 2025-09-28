/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:46:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/06/16 14:03:12 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/util.h"
#include "../libft/libft.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

static size_t	ft_extractor(char const *n, size_t k, size_t s, char t)
{
	size_t	j;
	int		o;

	o = 0;
	j = 0;
	while (s < k)
	{
		if (n[s] == '"' || n[s] == 39)
			o = 1;
		if (n[s] == t && o == 0)
			j++;
		s++;
		if (n[s] == '"' || n[s] == 39)
			o = 0;
	}
	return (j - 1);
}

static char	*ft_survivor(char const *n, size_t k, size_t s, char t)
{
	char	*p2;
	size_t	i;
	size_t	p;
	int		o;

	o = 0;
	i = 0;
	p2 = NULL;
	p = ft_extractor(n, k, s, t);
	p2 = malloc(k - s - p);
	if (!p2)
		return (NULL);
	while (s < k)
	{
		while (n[s] == t && o == 0)
			s++;
		if (n[s] == '"' || n[s] == 39)
			o = 1;
		p2[i] = n[s];
		s++;
		i++;
		if (n[s] == '"' || n[s] == 39)
			o = 0;
	}
	p2[i] = '\0';
	return (p2);
}

static size_t	ft_worldette(const char *s, char c)
{
	size_t	count;
	size_t	i;
	int		o;

	o = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			if (s[i] == '"' || s[i] == 39)
				o = 1;
			while (s[i] && (s[i] != c || o == 1))
			{
				i++;
				if (s[i] == '"' || s[i] == 39)
					o = 0;
			}
		}
	}
	return (count);
}

static char	**ft_rapt(char const *s, char c, char **p3, size_t size)
{
	size_t	r;
	size_t	n;
	int		b;

	b = 0;
	r = -1;
	n = 0;
	while (s[size])
	{
		if (s[size] == 39 || s[size] == '"')
			b = 1;
		size++;
		while (s[size] && b == 1)
		{
			if ((s[size] == 39 || s[size] == '"'))
				b = 0;
			size++;
		}
		if (s[size] == c || s[size] == '\0')
		{
			if (s[size - 1] != c)
			{
				p3[++r] = ft_survivor(s, size, n, c);
				if (!p3[r])
				{
					while (r != 0)
						free(p3[r-- - 1]);
					free(p3);
					return (NULL);
				}
				n = size;
			}
		}
	}
	return (p3);
}

char	**ft_split2(char const *s, char c)
{
	char	**p3;
	size_t	size;

	p3 = NULL;
	size = 0;
	if (!s)
		return (NULL);
	p3 = (char **)ft_calloc((ft_worldette(s, c) + 1), sizeof(char *));
	if (!p3)
		return (NULL);
	return (ft_rapt(s, c, p3, size));
}
