/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_state_lifecycle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:42:50 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/09 16:03:25 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_state_internal.h"

t_mini_state *mini_state_create(int args, char **environment_var_str_array)
{
	t_mini_state *state;

	state = (t_mini_state *)malloc(sizeof(t_mini_state));
	if (args == 1)
		state->environment_vars = env_deserialize(environment_var_str_array + 2);
	else
		state ->environment_vars = env_deserialize(environment_var_str_array + 1);
	if (!state->environment_vars)
		return NULL;
	state->last_command = NULL;
	state->last_opened_file = NULL;
	state->exit_after_last_command = false;
	return (state);
}

void mini_state_destroy(t_mini_state *state)
{
	if (!state)
		return ;
	env_destroy(state->environment_vars);
	free(state->last_command);
	free(state->last_opened_file);
	free(state);
}