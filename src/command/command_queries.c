/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_queries.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 04:47:07 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/09 21:00:01 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"

bool	command_is_built_in(t_command *command)
{
	if (!command)
		return (false);
	return (command->is_builtin);
}

char	*command_get_name(t_command *command)
{
	if (!command)
		return (NULL);
	return ((char *)gen_list_peek_top(command->args));
}
