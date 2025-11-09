/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:56:27 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/09 14:37:46 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/executer.h"
#include "include/environment.h"
#include "include/signal_manager.h"
#include "include/history_manager.h"
#include "include/ms_status_codes.h"
# include "external/gen_list/gen_list.h"
#include "external/libft/libft.h"
#include "include/mini_state.h"

#include "readline/readline.h"
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>


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

static void handle_system_status_codes(int status_code, t_mini_state *mini_state)
{
	if (status_code == MS_OK)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 0);
		return;
	}
	else if (status_code == MS_OPEN_ERR)
	{
		fprintf(stderr, "minishell: %s: %s\n", mini_state_get_last_opened_file(mini_state), strerror(errno));
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 1);
        return;
	}
	else if (status_code == MS_ALLOCATION_ERR)
	{
		perror("Malloc error");
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 1);
		exit(EXIT_FAILURE);
	}
	else if (status_code == MS_SIGNAL_ERR)
	{
		perror("Signal error");
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 1);
		exit(EXIT_FAILURE);
	}
	else
		fprintf(stderr, "Unhandled system status code: %d\n", status_code);
}

static void handle_command_status_codes(int status_code, t_mini_state *mini_state)
{
	if(status_code == COMMAND_NOT_FOUND_ERR)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 127);
		fprintf(stderr, "%s: command not found\n", mini_state_get_last_opened_file(mini_state));
	}
	else if(status_code == COMMAND_PERMISSION_ERR)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 126);
		fprintf(stderr, "%s: %s\n", mini_state_get_last_opened_file(mini_state), strerror(errno));
	}
	else if(status_code == COMMAND_IS_DIR_ERR)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 126);
		fprintf(stderr, "%s: Is a directory\n", mini_state_get_last_opened_file(mini_state));
	}
	else if(status_code == COMMAND_TOO_MANY_ARGS_ERR)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 1);
		fprintf(stderr, "minishell: too many arguments\n");
	}
	else if(status_code == COMMAND_MISSING_ARGS_ERR)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 1);
		fprintf(stderr, "minishell: missing arguments\n");
	}
	else if(status_code == COMMAND_NUMERIC_ARG_REQUIRED_ERR)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 2);
		fprintf(stderr, "minishell: numeric argument required\n");
	}
	else
		fprintf(stderr, "Unhandled command status code: %d\n", status_code);
}

static void handle_executer_status_codes(int status_code, t_mini_state *mini_state)
{
	if(status_code == EXECUTER_ERR)
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 2);
	else
		fprintf(stderr, "Unhandled executer status code: %d\n", status_code);
}

static void handle_lexer_status_codes(int status_code, t_mini_state *mini_state)
{
	if(status_code == LEXER_ERR)
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 2);
	else
		fprintf(stderr, "Unhandled lexer status code: %d\n", status_code);
}
static void handle_parser_status_codes(int status_code, t_mini_state *mini_state)
{
	if(status_code == PARSER_ERR)
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 2);
	else
		fprintf(stderr, "Unhandled parser status code: %d\n", status_code);
}

static void handle_redirect_status_codes(int status_code, t_mini_state *mini_state)
{
	if(status_code == REDIRECT_MALFORMED_ERR || status_code == REDIRECT_NO_HEADERDOC_DELIMITER_ERR )
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 2);
	else
		fprintf(stderr, "Unhandled redirect status code: %d\n", status_code);
}

static void	handle_status_codes(int status_code, t_mini_state *mini_state)
{
	if (status_code >= EXTERNALY_DEFINED_STATUS_CODE)
	{
		env_set_last_status_code( mini_state_get_environment_vars(mini_state), status_code - EXTERNALY_DEFINED_STATUS_CODE);
		if (mini_state_get_last_command(mini_state) && ft_strncmp(mini_state_get_last_command(mini_state), "exit", 4) == 0)
		{
			exit(status_code - EXTERNALY_DEFINED_STATUS_CODE);
		}
	}
	else if (status_code >= SYSTEM_STATUS_BEGIN && status_code <= SYSTEM_STATUS_END)
		handle_system_status_codes(status_code, mini_state);
	else if (status_code >= COMMAND_STATUS_BEGIN && status_code <= COMMAND_STATUS_END)
		handle_command_status_codes(status_code, mini_state);
	else if (status_code >= EXECUTER_STATUS_BEGIN && status_code <= EXECUTER_STATUS_END)
		handle_executer_status_codes(status_code, mini_state);
	else if (status_code >= LEXER_STATUS_BEGIN && status_code <= LEXER_STATUS_END)
		handle_lexer_status_codes(status_code, mini_state);
	else if (status_code >= PARSER_STATUS_BEGIN && status_code <= PARSER_STATUS_END)
		handle_parser_status_codes(status_code, mini_state);
	else if (status_code >= REDIRECT_MANAGER_STATUS_BEGIN && status_code <= REDIRECT_MANAGER_STATUS_END)
		handle_redirect_status_codes(status_code, mini_state);
	else
		fprintf(stderr, "Unhandled status code: %d\n", status_code);

}



int	main(int args, char **environment_var_str_array)
{
	t_mini_state	*mini_state;
	bool		finish;
	char		*input;

	mini_state = mini_state_create(args, environment_var_str_array);
	if (!mini_state)
		handle_status_codes(MS_ALLOCATION_ERR, mini_state);
	handle_status_codes(signals_init_interactive(), mini_state);
	finish = false;
	while (!finish)
	{
		input = get_input(mini_state_get_environment_vars(mini_state));
		if (input == NULL)
			finish = true;
		if (ft_strlen(input) != 0)
		{
			history_add(input);
			handle_status_codes(execute_line(input, mini_state), mini_state);
			free(input);
			input = NULL;
		}
	}
	mini_state_destroy(mini_state);
}
