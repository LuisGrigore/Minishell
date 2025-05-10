#ifndef BIN_COMMAND_EXECUTION_H
# define BIN_COMMAND_EXECUTION_H

#include "../include/minishell.h"
#include "../include/envioroment.h"
#include "../include/util.h"


void	exec_command(t_command *cmd, t_envioroment *envioroment);
char	*find_command(char **env, char *cmd);

# endif