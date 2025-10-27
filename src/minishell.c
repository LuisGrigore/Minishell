/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:56:27 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/27 18:41:33 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/executer.h"
#include "include/environment.h"
#include "include/signal_manager.h"
#include "include/history_manager.h"
# include "external/gen_list/gen_list.h"
#include "external/libft/libft.h"

#include "readline/readline.h"
#include <stdbool.h>


char	*get_line_tag(t_gen_list *env)
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

char *get_input(t_gen_list *env)
{
	char *line_tag;
	char *input;
	
	line_tag = get_line_tag(env);
	input = readline(line_tag);
	free(line_tag);
	return (input);
}
//TOD :: revisar esto
static void	handle_errors(int status_code)
{
	if (status_code == MS_OK)
	{
		return;
	}
	if (status_code == MS_ALLOCATION_ERR)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	else if (status_code == MS_SIGNAL_ERR)
	{
		perror("Signal error");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("Unknown error");
		exit(EXIT_FAILURE);
	}
}

int	main(int args, char **environment_var_str_array)
{
	t_gen_list	*environment_vars;
	bool		finish;
	char		*input;
	char		*expanded_input;

	if (args == 1)
		environment_vars = env_deserialize(environment_var_str_array + 2);
	else
		environment_vars = env_deserialize(environment_var_str_array + 1);
	if (!environment_vars)
		handle_errors(MS_ALLOCATION_ERR);
	handle_errors(signals_init_interactive());
	finish = false;
	while (!finish)
	{
		input = get_input(environment_vars);
		if ((ft_strlen(input) != 0 && ft_strncmp(input, "exit",
					ft_strlen(input)) == 0) || input == NULL)
			finish = true;
		else if (ft_strlen(input) != 0)
		{
			history_add(input);
			expanded_input = env_expand_vars(environment_vars,input);
			free(input);
			input = NULL;
			handle_errors(execute_line(expanded_input, environment_vars));
			free(expanded_input);
			expanded_input = NULL;
		}
	}
	env_destroy(environment_vars);
}
