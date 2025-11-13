/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_link_list_serialization_a.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 04:34:01 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 04:35:00 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gen_link_list_internal.h"

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
