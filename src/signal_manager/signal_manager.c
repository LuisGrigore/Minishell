#include "signal_manager_internal.h"
#include <stdio.h>
#include <stdlib.h>

static  volatile sig_atomic_t	g_signal = 0;

static void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	set_signal(int sig, void (*handler)(int))
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
	t_ms_status_code ret;

	ret = set_signal(SIGINT, sigint_handler);
	if (ret != MS_OK)
		return (ret);
	ret = set_signal(SIGQUIT, SIG_IGN);
	return (ret);
}


static void sigint_handler_heredoc(int sig)
{
    (void)sig;
    g_signal = SIGINT;
    write(1, "\n", 1);
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

int	signals_restore(void)
{
	t_ms_status_code	ret;

	ret = set_signal(SIGINT, SIG_DFL);
	if (ret != MS_OK)
		return (ret);
	ret = set_signal(SIGQUIT, SIG_DFL);
	return (ret);
}