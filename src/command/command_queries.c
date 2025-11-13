/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_queries.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 04:47:07 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 18:09:45 by lgrigore         ###   ########.fr       */
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
	if (!command || gen_list_is_empty(command->args))
		return (NULL);
	return ((char *)gen_list_peek_top(command->args));
}

void	print_command(void *cmd_ptr, void *index_ptr)
{
	t_command *cmd = (t_command *)cmd_ptr;
	int index = *(int *)index_ptr;
	// DEBUG
	printf("ptr:%p %p\n", cmd, cmd->command_funct);
	if (!cmd)
		return ;

	printf("Command #%d:\n", index);

	// Imprimir args
	if (cmd->args && !gen_list_is_empty(cmd->args))
	{
		printf("  Args:\n");

		t_gen_list_iter *arg_it = gen_list_iter_start(cmd->args);
		char *arg;
		while ((arg = (char *)gen_list_iter_next(arg_it)) != NULL)
		{
			printf("    %s\n", arg);
		}
	}
	else
	{
		printf("  Args: (none)\n");
	}

	// Imprimir redirects
	if (cmd->redirects && !gen_list_is_empty(cmd->redirects))
	{
		printf("  Redirects:\n");
		gen_list_for_each(cmd->redirects, print_redirect);
	}
	else
	{
		printf("  Redirects: (none)\n");
	}

	printf("\n");
	*(int *)index_ptr++;
}