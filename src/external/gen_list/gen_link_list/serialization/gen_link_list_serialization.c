/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_serialization.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:45:04 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/01 14:05:39 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

static void	free_str_array(char **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		free(arr[i++]);
	free(arr);
}

static size_t	calc_total_len(t_gen_list *list, t_element_to_string f)
{
	t_gen_list_iter	*it;
	void			*elem;
	char			*s;
	size_t			len;

	it = gen_list_iter_start(list);
	if (!it)
		return (0);
	len = 2;
	elem = gen_list_iter_next(it);
	while (elem)
	{
		s = f(elem);
		if (!s)
			return (gen_list_iter_destroy(it), 0);
		len += str_len(s);
		free(s);
		elem = gen_list_iter_next(it);
		if (elem)
			len += 2;
	}
	gen_list_iter_destroy(it);
	return (len);
}

static bool	fill_string(t_gen_list *list, t_element_to_string f, char *res,
		size_t *pos)
{
	t_gen_list_iter	*it;
	void			*elem;
	char			*s;

	it = gen_list_iter_start(list);
	if (!it)
		return (false);
	elem = gen_list_iter_next(it);
	while (elem)
	{
		s = f(elem);
		if (!s)
			return (gen_list_iter_destroy(it), false);
		str_copy_at(res, s, pos);
		free(s);
		elem = gen_list_iter_next(it);
		if (elem)
		{
			res[(*pos)++] = ',';
			res[(*pos)++] = ' ';
			res[*pos] = '\0';
		}
	}
	gen_list_iter_destroy(it);
	return (true);
}

char	*gen_list_serialize_to_string(t_gen_list *list, t_element_to_string f)
{
	char	*res;
	size_t	len;
	size_t	pos;

	if (!list || !f)
		return (NULL);
	len = calc_total_len(list, f);
	if (!len)
		return (NULL);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	pos = 0;
	res[pos++] = '[';
	res[pos] = '\0';
	if (!fill_string(list, f, res, &pos))
		return (free(res), NULL);
	res[pos++] = ']';
	res[pos] = '\0';
	return (res);
}

char	**gen_list_serialize_to_string_array(t_gen_list *list,
		t_element_to_string f)
{
	t_gen_list_iter	*it;
	void			*elem;
	char			**arr;
	size_t			i;

	if (!list || !f)
		return (NULL);
	arr = malloc((list->size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	it = gen_list_iter_start(list);
	if (!it)
		return (free(arr), NULL);
	i = 0;
	elem = gen_list_iter_next(it);
	while (elem)
	{
		arr[i] = f(elem);
		if (!arr[i])
			return (gen_list_iter_destroy(it), free_str_array(arr, i), NULL);
		i++;
		elem = gen_list_iter_next(it);
	}
	gen_list_iter_destroy(it);
	arr[i] = NULL;
	return (arr);
}

t_gen_list	*gen_list_deserialize_from_string_array(char **array,
		t_string_to_element conv)
{
	t_gen_list	*list;
	void		*val;
	size_t		i;

	if (!array || !conv)
		return (NULL);
	list = gen_list_create();
	if (!list)
		return (NULL);
	i = 0;
	while (array[i])
	{
		val = conv(array[i]);
		if (!val)
			return (gen_list_destroy(list, free), NULL);
		gen_list_push_back(list, val);
		i++;
	}
	return (list);
}
