#ifndef BIN_COMMAND_EXECUTION_H
# define BIN_COMMAND_EXECUTION_H

#include "envioroment.h"
#include "command.h"
#include "util.h"


void	exec_command(t_command *cmd, t_envioroment_var *envioroment);
char	*find_command(char **env, char *cmd);
void	children(int *pipes, t_command *cmd, char **env);;

# endif