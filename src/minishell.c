/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:56:27 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/12 23:44:43 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "external/gen_list/gen_list.h"
#include "external/libft/libft.h"
#include "include/environment.h"
#include "include/executer.h"
#include "include/handle_status_code.h"
#include "include/history_manager.h"
#include "include/mini_state.h"
#include "include/ms_status_codes.h"
#include "include/signal_manager.h"
#include "readline/readline.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

char	*get_line_tag(t_environment *env)
{
	char	*username;
	char	*line_tag;

	username = env_get(env, "LOGNAME");
	if (!username)
		return (ft_strdup("minishell%"));
	line_tag = ft_strjoin(username, "%>$");
	free(username);
	return (line_tag);
}

char	*get_input(t_environment *env)
{
	char	*line_tag;
	char	*input;

	line_tag = get_line_tag(env);
	input = readline(line_tag);
	free(line_tag);
	line_tag = NULL;
	return (input);
}

int	main(int args, char **environment_var_str_array)
{
	t_mini_state	*mini_state;
	char			*input;

	mini_state = mini_state_create(args, environment_var_str_array);
	if (!mini_state)
		handle_status_codes(MS_ALLOCATION_ERR, mini_state, NULL);
	handle_status_codes(signals_init_interactive(), mini_state, NULL);
	env_set_last_status_code(mini_state_get_environment(mini_state), 0);
	while (1)
	{
		input = get_input(mini_state_get_environment(mini_state));
		if (input == NULL)
			break ;
		if (ft_strlen(input) != 0)
		{
			history_add(input);
			handle_status_codes(execute_line(input, mini_state), mini_state,
				input);
			input = NULL;
		}
	}
	if (input)
		free(input);
	mini_state_destroy(mini_state);
}
