/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_status_code_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:13:33 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 20:29:27 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_status_code_internal.h"
#include "readline/readline.h"

static int	handle_system_status_codes_a(int status_code,
		t_mini_state *mini_state)
{
	if (status_code == MS_OK)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 0);
		return (1);
	}
	else if (status_code == MS_OPEN_ERR)
	{
		ft_printf("minishell: %s: %s\n",
			mini_state_get_last_opened_file(mini_state), strerror(errno));
		env_set_last_status_code(mini_state_get_environment(mini_state), 1);
		return (1);
	}
	else if (status_code == MS_PATH_ERR)
	{
		ft_printf("minishell: %s: No such file or directory\n",
			mini_state_get_last_command(mini_state));
		env_set_last_status_code(mini_state_get_environment(mini_state), 1);
		return (1);
	}
	else if (status_code == MS_CNTRL_ERR)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 1);
		return (destroy_temp_fles(mini_state), 1);
	}
	return (MS_OK);
}

static void	handle_system_status_codes_b(int status_code,
		t_mini_state *mini_state)
{
	if (status_code == MS_ALLOCATION_ERR)
	{
		ft_printf("Malloc error");
		env_set_last_status_code(mini_state_get_environment(mini_state), 1);
		mini_state_destroy(mini_state);
		exit(EXIT_FAILURE);
	}
	else if (status_code == MS_SIGNAL_ERR)
	{
		perror("Signal error");
		env_set_last_status_code(mini_state_get_environment(mini_state), 1);
		mini_state_destroy(mini_state);
		exit(EXIT_FAILURE);
	}
	else
		ft_printf("Unhandled system status code: %d\n", status_code);
}

void	handle_system_status_codes(int status_code, t_mini_state *mini_state)
{
	if (handle_system_status_codes_a(status_code, mini_state) != 0)
		return ;
	handle_system_status_codes_b(status_code, mini_state);
}

void	handle_status_codes(int status_code, t_mini_state *mini_state,
		char *input)
{
	int	exit_status;

	free(input);
	if (status_code >= EXTERNALY_DEFINED_STATUS_CODE)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state),
			status_code - EXTERNALY_DEFINED_STATUS_CODE);
		if (mini_state_get_last_command(mini_state)
			&& ft_strncmp(mini_state_get_last_command(mini_state), "exit",
				4) == 0)
		{
			mini_state_destroy(mini_state);
			history_clean();
			exit(status_code - EXTERNALY_DEFINED_STATUS_CODE);
		}
	}
	select_function_to_handle(status_code, mini_state);
	if (mini_state_get_exit_after_last_command(mini_state))
	{
		exit_status = env_get_last_status_code(
				mini_state_get_environment(mini_state));
		mini_state_destroy(mini_state);
		history_clean();
		exit(exit_status);
	}
}
