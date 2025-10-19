/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:07:32 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/19 20:08:03 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

// TODO:: quitar esto
void	print_commands(t_gen_list *commands)
{
	t_gen_list_iter	*it;
	t_command		*cmd;
	int				index;

	if (!commands || gen_list_is_empty(commands))
	{
		printf("No commands to print.\n");
		return ;
	}
	it = gen_list_iter_start(commands);
	index = 1;
	cmd = (t_command *)gen_list_iter_next(it);
	while (cmd != NULL)
	{
		print_command(cmd, index++);
		cmd = (t_command *)gen_list_iter_next(it);
	}
}
