/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 06:00:00 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 17:59:37 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_INTERNAL_H
# define COMMAND_INTERNAL_H

# include "../external/gen_list/gen_list.h"
# include "../external/libft/libft.h"
# include "../include/command.h"
# include "../include/environment.h"
# include "../include/signal_manager.h"
# include "../include/util.h"
# include <stdbool.h>
# include <stdlib.h>

typedef int			(*t_command_funct)(t_command *, t_environment *);

struct				s_command
{
	t_gen_list		*args;
	t_gen_list		*redirects;
	bool			is_builtin;
	t_command_funct	command_funct;
};

int					pwd_execute(t_command *command, t_environment *environment);
int					bin_execute(t_command *cmd, t_environment *environment);
int					cd_execute(t_command *command, t_environment *environment);
int					pwd_execute(t_command *command, t_environment *envioroment);
int					export_execute(t_command *command,
						t_environment *environment);
int					unset_execute(t_command *command,
						t_environment *environment);
int					env_execute(t_command *command, t_environment *environment);
int					echo_execute(t_command *command,
						t_environment *environment);
int					exit_execute(t_command *command,
						t_environment *environment);
char				*find_command(char **env, char *cmd, int *err_out);
t_command_funct	get_command_function(char *cmd_name);

#endif