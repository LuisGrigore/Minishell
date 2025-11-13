/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_operations_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 05:52:48 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 18:07:46 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"

static int	handle_list_errors(t_gen_list_status_code list_status_code)
{
	if (list_status_code == GEN_LIST_OK)
		return (MS_OK);
	else if (list_status_code == GEN_LIST_MALLOC_ERR)
		return (MS_ALLOCATION_ERR);
	else if (list_status_code == GEN_LIST_IS_NULL_ERR)
		return (COMMAND_MALFORMED_ERR);
	else
		return (COMMAND_ERR);
}

int	command_push_arg(t_command *command, char *arg)
{
	return (handle_list_errors(gen_list_push_back(command->args,
				ft_strdup(arg))));
}

int	command_push_redirect(t_command *command, t_redirect_type redirect_type,
		char *file_name)
{
	return (handle_list_errors(gen_list_push_back(command->redirects,
				redirect_create(redirect_type, file_name))));
}
void command_set_name(t_command *command, char *name)
{
	gen_list_push_front(command->args, ft_strdup(name));
	command->command_funct = get_command_function(name);
}
