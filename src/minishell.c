/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:56:27 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/07 16:37:41 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/executer.h"
#include "include/environment.h"
#include "include/signal_manager.h"
#include "include/history_manager.h"
#include "include/ms_status_codes.h"
# include "external/gen_list/gen_list.h"
#include "external/libft/libft.h"

#include "readline/readline.h"
#include <stdbool.h>
#include <stdio.h>

static void handle_errors_debug(t_ms_status_code status_code)
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
			perror("bash: FILE_NAME");
            return;

        // Command status codes
        case COMMAND_SUCCESS:
            printf("COMMAND_SUCCESS\n");
            return;
        case COMMAND_ERROR:
            printf("COMMAND_ERROR\n");
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
        case BINBUILTIN_SUCCESS:
            printf("BINBUILTIN_SUCCESS\n");
            return;
        case BINBUILTIN_ERROR:
            printf("BINBUILTIN_ERROR\n");
            exit(status_code);
        case BINBUILTIN_NOT_FOUND_ERR:
            printf("BINBUILTIN_NOT_FOUND_ERR\n");
            exit(status_code);
        case BINBUILTIN_PERMISSION_ERR:
            printf("BINBUILTIN_PERMISSION_ERR\n");
            exit(status_code);
        case BUILTIN_TOO_MANY_ARGS:
            printf("BUILTIN_TOO_MANY_ARGS\n");
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
        case EXIT_USER_DEFINED_STATUS_CODE:
            printf("EXIT_USER_DEFINED_STATUS_CODE\n");
            exit(status_code - EXIT_USER_DEFINED_STATUS_CODE_BEGIN);

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
//TOD :: revisar esto
static void	handle_errors(int status_code)
{
	if (status_code == MS_OK)
	{
		return;
	}
	if (status_code >= EXIT_USER_DEFINED_STATUS_CODE)
	{
		exit(status_code - EXIT_USER_DEFINED_STATUS_CODE);
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
	else if(status_code / 100 == 1)
		exit(EXIT_FAILURE);
	
	else if(status_code / 100 == 2)
	{
		perror("Environment error");
		exit(EXIT_FAILURE);
	}
	else if(status_code / 100 == 3)
	{
		perror("Lexer error");
		exit(EXIT_FAILURE);
	}
	else if(status_code / 100 == 4)
	{
		perror("Parser error");
		exit(EXIT_FAILURE);
	}
	else if(status_code / 100 == 8)
	{
		perror("Invalide file descriptor");
		exit(EXIT_FAILURE);
	}

}

typedef struct s_mini_state
{
	t_gen_list	*environment_vars;
	char *last_command;
	char *last_opened_file;
} t_mini_state;

t_mini_state *mini_state_create(int args, char **environment_var_str_array)
{
	t_mini_state *state;

	state = malloc(sizeof(t_mini_state));
	if (args == 1)
		state->environment_vars = env_deserialize(environment_var_str_array + 2);
	else
		state ->environment_vars = env_deserialize(environment_var_str_array + 1);
	if (!state->environment_vars)
		return NULL;
	state->last_command = NULL;
	state->last_opened_file = NULL;
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

int	main(int args, char **environment_var_str_array)
{
	t_mini_state	*state;
	bool		finish;
	char		*input;
	//char		*expanded_input;

	state = mini_state_create(args, environment_var_str_array);
	if (!state)
		handle_errors(MS_ALLOCATION_ERR);
	handle_errors(signals_init_interactive());
	finish = false;
	while (!finish)
	{
		input = get_input(state->environment_vars);
		if (input == NULL)
			finish = true;
		if (ft_strlen(input) != 0)
		{
			history_add(input);
			handle_errors_debug(execute_line(input, state->environment_vars));
			free(input);
			input = NULL;
		}
	}
	mini_state_destroy(state);
}
