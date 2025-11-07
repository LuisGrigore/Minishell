/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:56:27 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/07 20:41:40 by lgrigore         ###   ########.fr       */
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

static void handle_errors_debug(t_ms_status_code status_code, t_mini_state *mini_state)
{
    switch (status_code)
    {
        // System status codes
        case MS_OK:
            printf("MS_OK\n");
            return;
        case MS_FORK_ERR:
            printf("MS_FORK_ERR\n");
            exit(status_code);
        case MS_PIPE_ERR:
            printf("MS_PIPE_ERR\n");
            exit(status_code);
        case MS_DUP2_ERR:
            printf("MS_DUP2_ERR\n");
            exit(status_code);
        case MS_ALLOCATION_ERR:
            printf("MS_ALLOCATION_ERR\n");
            exit(status_code);
        case MS_CLOSE_ERR:
            printf("MS_CLOSE_ERR\n");
            exit(status_code);
        case MS_SIGNAL_ERR:
            printf("MS_SIGNAL_ERR\n");
            exit(status_code);
        case MS_OPEN_ERR:
			fprintf(stderr, "bash: %s: %s\n", mini_state_get_last_opened_file(mini_state), strerror(errno));
            return;

        // Command status codes
        case COMMAND_SUCCESS:
            printf("COMMAND_SUCCESS\n");
            return;
        case COMMAND_ERR:
            printf("COMMAND_ERR\n");
            exit(status_code);
        case COMMAND_MALFORMED_ERR:
            printf("COMMAND_MALFORMED_ERR\n");
            exit(status_code);
        case COMMAND_NOT_FOUND_ERR:
            printf("COMMAND_NOT_FOUND_ERR\n");
            exit(status_code);
        case COMMAND_PERMISSION_ERR:
            printf("COMMAND_PERMISSION_ERR\n");
            exit(status_code);
        case COMMAND_IS_DIR_ERR:
            printf("COMMAND_IS_DIR_ERR\n");
            exit(status_code);

        // Builtin status codes

        case BINBUILTIN_ERROR:
            printf("BINBUILTIN_ERROR\n");
            exit(status_code);
        case COMMAND_TOO_MANY_ARGS_ERR:
            printf("COMMAND_TOO_MANY_ARGS_ERR\n");
            exit(status_code);

        // Environment status codes
        case ENVIRONMENT_ERR:
            printf("ENVIRONMENT_ERR\n");
            exit(status_code);

        // Executer status codes
        case EXECUTER_ERR:
            printf("EXECUTER_ERR\n");
            exit(status_code);

        // Lexer status codes
        case LEXER_ERR:
            printf("LEXER_ERR\n");
            exit(status_code);
        case LEXER_NULL_ERR:
            printf("LEXER_NULL_ERR\n");
            exit(status_code);
        case LEXER_SYNTAX_ERR:
            printf("LEXER_SYNTAX_ERR\n");
            exit(status_code);

        // Parser status codes
        case PARSER_ERR:
            printf("PARSER_ERR\n");
            exit(status_code);
        case PARSER_NULL_ERR:
            printf("PARSER_NULL_ERR\n");
            exit(status_code);

        // Redirect status codes
        case REDIRECT_MANAGER_SUCCESS:
            printf("REDIRECT_MANAGER_SUCCESS\n");
            return;
        case REDIRECT_MALFORMED_ERR:
            printf("REDIRECT_MALFORMED_ERR\n");
            exit(status_code);
        case REDIRECT_NO_HEADERDOC_DELIMITER_ERR:
            printf("REDIRECT_NO_HEADERDOC_DELIMITER_ERR\n");
            exit(status_code);
        case REDIRECT_INVALID_FD_ERR:
            printf("REDIRECT_INVALID_FD_ERR\n");
            exit(status_code);

        // Exit status codes
        case EXTERNALY_DEFINED_STATUS_CODE:
            printf("EXTERNALY_DEFINED_STATUS_CODE\n");
            exit(status_code - EXTERNALY_DEFINED_STATUS_CODE);

        default:
            printf("UNKNOWN_ERROR_CODE: %d\n", status_code);
            exit(EXIT_FAILURE);
    }
}


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
static void	handle_errors(int status_code, t_mini_state *mini_state)
{
	if (status_code == MS_OK)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 0);
		return;
	}
	else if (status_code >= EXTERNALY_DEFINED_STATUS_CODE)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), status_code - EXTERNALY_DEFINED_STATUS_CODE);
		if (ft_strncmp(mini_state_get_last_command(mini_state), "exit", 4) == 0)
		{
			exit(status_code - EXTERNALY_DEFINED_STATUS_CODE);
		}
		
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
	else if(status_code == PARSER_ERR)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 2);
		//exit(EXIT_FAILURE);
	}
	else if(status_code == LEXER_ERR)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 2);
		//exit(EXIT_FAILURE);
	}
	else if(status_code == EXECUTER_ERR)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 2);
		//exit(EXIT_FAILURE);
	}
	else if(status_code == REDIRECT_MALFORMED_ERR || status_code == REDIRECT_NO_HEADERDOC_DELIMITER_ERR ||
		 status_code == REDIRECT_INVALID_FD_ERR)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 2);
		//exit(EXIT_FAILURE);
	}
	else if(status_code == COMMAND_NOT_FOUND_ERR)
	{
		env_set_last_status_code(mini_state_get_environment_vars(mini_state), 127);
		fprintf(stderr, "%s: command not found\n", mini_state_get_last_opened_file(mini_state));
		//exit(EXIT_FAILURE);
	}
	else
		printf("Unhandled error code: %d\n", status_code);

}



int	main(int args, char **environment_var_str_array)
{
	t_mini_state	*mini_state;
	bool		finish;
	char		*input;

	mini_state = mini_state_create(args, environment_var_str_array);
	if (!mini_state)
		handle_errors(MS_ALLOCATION_ERR, mini_state);
	handle_errors(signals_init_interactive(), mini_state);
	finish = false;
	while (!finish)
	{
		input = get_input(mini_state_get_environment_vars(mini_state));
		if (input == NULL)
			finish = true;
		if (ft_strlen(input) != 0)
		{
			history_add(input);
			handle_errors(execute_line(input, mini_state), mini_state);
			free(input);
			input = NULL;
		}
	}
	mini_state_destroy(mini_state);
}
