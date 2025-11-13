/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_operations_a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 05:41:23 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 01:51:33 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"
#include "unistd.h"

static int	command_redirects_execute(t_command *command,
		t_mini_state *mini_state)
{
	t_gen_list_iter	*it;
	t_redirect		*current_redirect;
	int				status_code;

	if (!command->redirects)
		return (COMMAND_MALFORMED_ERR);
	it = gen_list_iter_start(command->redirects);
	if (!it)
		return (MS_ALLOCATION_ERR);
	status_code = MS_OK;
	while (1)
	{
		current_redirect = (t_redirect *)gen_list_iter_next(it);
		if (!current_redirect || status_code != MS_OK)
			break ;
		status_code = redirect_execute(current_redirect, mini_state);
	}
	gen_list_iter_destroy(it);
	return (status_code);
}

int	command_exec(t_command *command, t_mini_state *mini_state)
{
	int	status_code;
	int	stdin_backup;
	int	stdout_backup;

	mini_state_set_last_command(mini_state,
		(char *)gen_list_peek_top(command->args));
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup == -1 || stdout_backup == -1)
		return (MS_ALLOCATION_ERR);
	status_code = command_redirects_execute(command, mini_state);
	if (status_code != MS_OK)
	{
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		return (close(stdout_backup), close(stdin_backup), status_code);
	}
	status_code = command->command_funct(command,
			mini_state_get_environment(mini_state));
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	return (close(stdin_backup), close(stdout_backup), status_code);
}

int	command_heredocs_create(t_gen_list *commands, t_mini_state *mini_state)
{
	t_gen_list_iter	*it;
	t_command		*actual_command;
	int				status_code;

	status_code = MS_OK;
	it = gen_list_iter_start(commands);
	actual_command = gen_list_iter_next(it);
	while (actual_command)
	{
		status_code = redirect_heredoc_check(actual_command->redirects,
				mini_state);
		actual_command = gen_list_iter_next(it);
		if (status_code != MS_OK)
			break ;
	}
	gen_list_iter_destroy(it);
	return (status_code);
}
int	command_heredocs_asignate(t_gen_list *commands, t_mini_state *mini_state)
{
	t_gen_list_iter	*it;
	t_command		*actual_command;
	int				status_code;

	status_code = MS_OK;
	it = gen_list_iter_start(commands);
	actual_command = gen_list_iter_next(it);
	while (actual_command)
	{
		status_code = redirect_heredoc_asignate(actual_command->redirects,
				mini_state);
		actual_command = gen_list_iter_next(it);
		if (status_code != MS_OK)
			break ;
	}
	gen_list_iter_destroy(it);
	return (status_code);
}
