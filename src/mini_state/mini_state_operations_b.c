/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_state_operations_b.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:02:00 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/12 04:04:26 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_state_internal.h"

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

void	mini_state_set_heredoc_temp_file(t_mini_state *state, int files)
{
	if (!state)
		return ;
	state->heredoc_temp_files = files;
}

void	destroy_temp_fles(t_mini_state *state)
{
	char	*temp;
	char	*itoa_result;

	while (state->heredoc_temp_files > 0)
	{
		itoa_result = ft_itoa(state->heredoc_temp_files);
		temp = ft_strjoin(PATH_HEREDOC_TEMP_FILE, itoa_result);
		unlink(temp);
		state->heredoc_temp_files--;
		free(temp);
		free(itoa_result);
	}
}
