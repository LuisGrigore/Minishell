/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_state_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:43:27 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/09 23:24:22 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_state_internal.h"
#include <stdio.h>

char	*mini_state_get_last_command(t_mini_state *state)
{
	if (!state)
		return (NULL);
	return (state->last_command);
}

char	*mini_state_get_last_opened_file(t_mini_state *state)
{
	if (!state)
		return (NULL);
	return (state->last_opened_file);
}
// t_gen_list *mini_state_get_environment(t_mini_state *state)
t_environment	*mini_state_get_environment(t_mini_state *state)

{
	if (!state)
		return (NULL);
	return (state->environment_vars);
}

void	mini_state_set_last_command(t_mini_state *state, const char *command)
{
	if (!state)
		return ;
	free(state->last_command);
	if (command)
		state->last_command = ft_strdup(command);
	else
		state->last_command = NULL;
}
void	mini_state_set_last_opened_file(t_mini_state *state,
		const char *file_name)
{
	if (!state)
		return ;
	free(state->last_opened_file);
	if (file_name)
		state->last_opened_file = ft_strdup(file_name);
	else
		state->last_opened_file = NULL;
}

bool	mini_state_get_exit_after_last_command(t_mini_state *state)
{
	if (!state)
		return (false);
	return (state->exit_after_last_command);
}

void	mini_state_set_exit_after_last_command(t_mini_state *state, bool value)
{
	if (!state)
		return ;
	state->exit_after_last_command = value;
}