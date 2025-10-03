#include "signal_manager_internal.h"
#include <stdio.h>
#include <stdlib.h>

void signals_init_interactive(void)
{
    perror("signals_init_interactive: not implemented");
    exit(EXIT_FAILURE);
}

void signals_init_execution(void)
{
    perror("signals_init_execution: not implemented");
    exit(EXIT_FAILURE);
}

void signals_init_heredoc(void)
{
    perror("signals_init_heredoc: not implemented");
    exit(EXIT_FAILURE);
}

void signals_restore(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}