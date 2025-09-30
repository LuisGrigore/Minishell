/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:11 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/01 00:02:21 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

size_t	str_len(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	str_copy_at(char *dest, const char *src, size_t *pos)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[*pos] = src[i];
		(*pos)++;
		i++;
	}
	dest[*pos] = '\0';
}
