/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:45:25 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 18:47:33 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_manager_internal.h"

volatile sig_atomic_t	g_signal = 0;

static void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	write(1, "", 1);
	rl_redisplay();
}

int	set_signal(int sig, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sig, &sa, NULL) == -1)
		return (MS_SIGNAL_ERR);
	return (MS_OK);
}

int	signals_init_interactive(void)
{
	t_ms_status_code	ret;

	ret = set_signal(SIGINT, sigint_handler);
	if (ret != MS_OK)
		return (ret);
	ret = set_signal(SIGQUIT, SIG_IGN);
	return (ret);
}

static void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	close(0);
}

int	signals_init_heredoc(void)
{
	t_ms_status_code	ret;

	ret = set_signal(SIGINT, sigint_handler_heredoc);
	if (ret != MS_OK)
		return (ret);
	ret = set_signal(SIGQUIT, SIG_IGN);
	return (ret);
}
