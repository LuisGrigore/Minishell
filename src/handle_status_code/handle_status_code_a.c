/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_status_code_a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:13:38 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/12 23:35:09 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_status_code_internal.h"

static void	handle_executer_status_codes(int status_code,
		t_mini_state *mini_state)
{
	if (status_code == EXECUTER_ERR)
		env_set_last_status_code(mini_state_get_environment(mini_state), 2);
	else
		ft_printf("Unhandled executer status code: %d\n", status_code);
}

static void	handle_lexer_status_codes(int status_code, t_mini_state *mini_state)
{
	if (status_code == LEXER_ERR)
		env_set_last_status_code(mini_state_get_environment(mini_state), 2);
	else if (status_code == LEXER_UNSUPORTED_CHARACTER_ERR)
		ft_printf("Minishell: Lexer: Unsuported_character \n");
	else if (status_code == LEXER_UNCLOSED_QUOTE_ERR)
		ft_printf("Minishell: Lexer: Unclosed quote detected\n");
	else if (status_code == LEXER_SYNTAX_ERR)
		ft_printf("Minishell: Lexer: Syntax error\n");
	else
		ft_printf("Minishell: Lexer: Unknown code error: %d\n", status_code);
}

static void	handle_parser_status_codes(int status_code,
		t_mini_state *mini_state)
{
	if (status_code == PARSER_ERR)
		env_set_last_status_code(mini_state_get_environment(mini_state), 2);
	else if (status_code == PARSER_SYNTAX_ERR)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 2);
		ft_printf("minishell: syntax error \n");
	}
	else
		ft_printf("Unhandled parser status code: %d\n", status_code);
}

static void	handle_redirect_status_codes(int status_code,
		t_mini_state *mini_state)
{
	if (status_code == REDIRECT_MALFORMED_ERR)
		env_set_last_status_code(mini_state_get_environment(mini_state), 2);
	else if (status_code == REDIRECT_NO_HEADERDOC_DELIMITER_ERR)
	{
		env_set_last_status_code(mini_state_get_environment(mini_state), 2);
		ft_printf("minishell: bash: warning: here-document\n");
	}
	else
		ft_printf("Unhandled redirect status code: %d\n", status_code);
}

void	select_function_to_handle(int status_code, t_mini_state *mini_state)
{
	int	stdout_backup;

	stdout_backup = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (status_code >= SYSTEM_STATUS_BEGIN && status_code <= SYSTEM_STATUS_END)
		handle_system_status_codes(status_code, mini_state);
	else if (status_code >= COMMAND_STATUS_BEGIN
		&& status_code <= COMMAND_STATUS_END)
		handle_command_status_codes(status_code, mini_state);
	else if (status_code >= EXECUTER_STATUS_BEGIN
		&& status_code <= EXECUTER_STATUS_END)
		handle_executer_status_codes(status_code, mini_state);
	else if (status_code >= LEXER_STATUS_BEGIN
		&& status_code <= LEXER_STATUS_END)
		handle_lexer_status_codes(status_code, mini_state);
	else if (status_code >= PARSER_STATUS_BEGIN
		&& status_code <= PARSER_STATUS_END)
		handle_parser_status_codes(status_code, mini_state);
	else if (status_code >= REDIRECT_MANAGER_STATUS_BEGIN
		&& status_code <= REDIRECT_MANAGER_STATUS_END)
		handle_redirect_status_codes(status_code, mini_state);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
}
