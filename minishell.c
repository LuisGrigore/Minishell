/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:56:27 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/01 14:59:12 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/bin_commandss_execution.h"
#include "include/command.h"
#include "include/environment.h"
# include "external/gen_list/gen_list.h"
#include "include/parser.h"
#include "include/redirect_asignation.h"
#include "parser/include/lexer.h"
#include "external/libft/libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal = 0;

static char	*history_checker(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '|' || cmd[ft_strlen(cmd)] == '|')
	{
		add_history(cmd);
		return (NULL);
	}
	while (cmd[i])
	{
		if (ft_ispace(cmd[i]) == 0)
			break ;
		i++;
	}
	if (cmd[i] == '\0')
		return (NULL);
	return (cmd);
}

char	*check_cmd(char *cmd)
{
	int	i;
	int	b;

	b = 0;
	i = 0;
	if (history_checker(cmd) == NULL)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '"')
			b = 1;
		i++;
		while (cmd[i] && b == 1)
		{
			if (cmd[i] == '"')
				b = 0;
			i++;
		}
	}
	if (b != 0)
	{
		add_history(cmd);
		return (NULL);
	}
	return (cmd);
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

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals_init(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	print_tokens(t_gen_list *tokens)
{
	t_gen_list_iter		*it;
	t_token		*tok;
	const char	*type_str;

	if (!tokens)
		return ;
	it = gen_list_iter_start(tokens);
	while ((tok = (t_token *)gen_list_iter_next(it)) != NULL)
	{
		switch (tok->type)
		{
		case TOKEN_CMD:
			type_str = "CMD";
			break ;
		case TOKEN_ARG:
			type_str = "ARG";
			break ;
		case TOKEN_PIPE:
			type_str = "PIPE";
			break ;
		case TOKEN_REDIR_IN:
			type_str = "REDIR_IN";
			break ;
		case TOKEN_REDIR_OUT:
			type_str = "REDIR_OUT";
			break ;
		case TOKEN_REDIR_APPEND:
			type_str = "REDIR_APPEND";
			break ;
		case TOKEN_HEREDOC:
			type_str = "HEREDOC";
			break ;
		default:
			type_str = "UNKNOWN";
			break ;
		}
		printf("[%s] : [%s]\n", type_str, tok->value);
	}
}

void print_redirect(void *redir_ptr) {
	t_redirect *redir = (t_redirect *) redir_ptr;
    if (!redir) return;
    const char *type_str;
    switch (redir->redirect_simbol) {
        case LEFT_REDIRECT: type_str = "<"; break;
        case RIGHT_REDIRECT: type_str = ">"; break;
        case DOUBLE_LEFT_REDIRECT: type_str = "<<"; break;
        case DOUBLE_RIGHT_REDIRECT: type_str = ">>"; break;
        case NONE: type_str = "NONE"; break;
        case ERROR: type_str = "ERROR"; break;
        default: type_str = "UNKNOWN"; break;
    }
    printf("    Redirect: %s %s\n", type_str, redir->file);
}

void print_command(t_command *cmd, int index) {
    if (!cmd) return;

    printf("Command #%d:\n", index);

    //Imprimir args
    if (cmd->args && !gen_list_is_empty(cmd->args)) {
        printf("  Args:\n");
        
		t_gen_list_iter *arg_it = gen_list_iter_start(cmd->args);
        char *arg;
        while ((arg = (char *)gen_list_iter_next(arg_it)) != NULL) {
            printf("    %s\n", arg);
        }
    } else {
        printf("  Args: (none)\n");
    }

    //Imprimir redirects
    if (cmd->redirects && !gen_list_is_empty(cmd->redirects)) {
        printf("  Redirects:\n");
        gen_list_for_each(cmd->redirects,print_redirect);
    } else {
        printf("  Redirects: (none)\n");
    }

    printf("\n");
}

void print_commands(t_gen_list *commands) {
    if (!commands || gen_list_is_empty(commands)) {
        printf("No commands to print.\n");
        return;
    }

    t_gen_list_iter *it = gen_list_iter_start(commands);
    t_command *cmd;
    int index = 1;
    while ((cmd = (t_command *)gen_list_iter_next(it)) != NULL) {
        print_command(cmd, index++);
    }
}

// void destroy_token_data(void *token_ptr)
// {
// 	destroy_token((t_token *) token_ptr);
// }

int	main(int args, char **environment_var_str_array)
{
	//t_gen_list	*tokens;
	t_gen_list	*current_commands;
	t_gen_list	*envioroment_vars;
	bool		finish;
	char		*line;
	char		*name;

	if (args > 1)
		exit(0);
	signals_init();
	envioroment_vars = env_deserialize(environment_var_str_array
			+ 2);
	name = get_line_tag(envioroment_vars);
	finish = false;
	while (!finish)
	{
		current_commands = NULL;
		line = readline(name);
		if ((ft_strlen(line) != 0 && ft_strncmp(line, "exit",
					ft_strlen(line)) == 0) || line == NULL)
			finish = true;
		else if (ft_strlen(line) != 0)
		{
			if (check_cmd(line) == NULL)
				continue ;
			add_history(line);
			// tokens = lexer_tokenize(line);
			// //print_tokens(tokens);
			// if (!tokens)
			// {
			// 	perror("Tokenization error ");
			// 	continue ;
			// }
			//current_commands = parse_tokens_to_commands(tokens);
			//gen_list_destroy(tokens, destroy_token_data);
			current_commands = parse_line(line);
			if (!current_commands)
			{
				perror("Parsing error ");
				continue ;
			}
			//print_commands(current_commands);
			execute_commands_with_pipes(current_commands, envioroment_vars);
		}
		free(line);
		line = NULL;
		gen_list_destroy(current_commands, destroy_command);
		current_commands = NULL;
	}
	env_destroy(envioroment_vars);
	free(name);
}
