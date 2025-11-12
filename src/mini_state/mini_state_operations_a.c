/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_state_operations_a.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:43:27 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/12 23:34:07 by dmaestro         ###   ########.fr       */
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

void	mini_state_set_heredoc_value(t_mini_state *state, int value)
{
	if (!state)
		return ;
	state->heredoc_exec = value;
}
