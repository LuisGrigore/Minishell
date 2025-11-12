/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_status_code_c.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:13:30 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/12 16:45:16 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_status_code_internal.h"

static int	handle_command_status_codes_a(int status_code,
		t_mini_state *mini_state)
{
	if (status_code == COMMAND_NOT_FOUND_ERR)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 127);
		return (ft_printf("minishell :%s: command not found\n",
				mini_state_get_last_command(mini_state)));
	}
	else if (status_code == COMMAND_PERMISSION_ERR)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 126);
		return (ft_printf("minishell: %s: %s\n",
				mini_state_get_last_command(mini_state), strerror(errno)));
	}
	else if (status_code == COMMAND_IS_DIR_ERR)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 126);
		return (ft_printf("minishell :%s: Is a directory\n",
				mini_state_get_last_command(mini_state)));
	}
	return (0);
}

static int	handle_command_status_codes_b(int status_code,
		t_mini_state *mini_state)
{
	if (status_code == COMMAND_NUMERIC_ARG_REQUIRED_ERR)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 2);
		return (ft_printf("minishell: %s: numeric argument required\n",
				mini_state_get_last_command(mini_state)));
	}
	else if (status_code == COMMAND_MALFORMED_ERR)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 1);
		return ((ft_printf("minishell: %s: not a valid identifier\n",
					mini_state_get_last_command(mini_state))));
	}
	else if (status_code == COMMAND_NO_SUCH_FILE_OR_DIR_ERR)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 127);
		return (ft_printf("minishell: %s: No such file or directory\n",
				mini_state_get_last_command(mini_state)));
	}
	return (0);
}

static void	handle_command_status_code_c(int status_code,
		t_mini_state *mini_state)
{
	if (status_code == COMMAND_TOO_MANY_ARGS_ERR)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 1);
		ft_printf("minishell: %s: too many arguments\n",
			mini_state_get_last_command(mini_state));
	}
	else if (status_code == COMMAND_MISSING_ARGS_ERR)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 1);
		ft_printf("minishell: %s: missing arguments\n",
			mini_state_get_last_command(mini_state));
	}
	else
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 1);
		ft_printf("minishell: %s: Unassigned error \n",
			mini_state_get_last_command(mini_state));
	}
}

void	handle_command_status_codes(int status, t_mini_state *mini_state)
{
	if (handle_command_status_codes_a(status, mini_state) != 0)
		return ;
	if (handle_command_status_codes_b(status, mini_state) != 0)
		return ;
	handle_command_status_code_c(status, mini_state);
}
