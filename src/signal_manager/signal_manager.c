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

void signals_init_interactive(void)
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


static void sigint_handler_heredoc(int sig)
{
    (void)sig;
    g_signal = SIGINT;       // marcar la señal recibida
    write(1, "\n", 1);       // nueva línea para que el heredoc se "interrumpa"
}

void signals_init_heredoc(void)
{
	struct sigaction sa_int;
    struct sigaction sa_quit;

    sa_int.sa_handler = sigint_handler_heredoc;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sa_int, NULL) == -1)
    {
        perror("sigaction(SIGINT) failed");
        exit(EXIT_FAILURE);
    }

    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;
    if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
    {
        perror("sigaction(SIGQUIT) failed");
        exit(EXIT_FAILURE);
    }
}

void signals_restore(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}