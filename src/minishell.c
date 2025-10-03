/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:56:27 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/03 15:00:22 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/bin_commandss_execution.h"
#include "include/command.h"
#include "include/environment.h"
# include "external/gen_list/gen_list.h"
#include "include/parser.h"
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


int	main(int args, char **environment_var_str_array)
{
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
			current_commands = parse_line(line);
			if (!current_commands)
			{
				perror("Parsing error ");
				continue ;
			}
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
