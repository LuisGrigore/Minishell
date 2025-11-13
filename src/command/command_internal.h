/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 06:00:00 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 20:40:53 by lgrigore         ###   ########.fr       */
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
t_command_funct		get_command_function(char *cmd_name);
void				double_pontier_free(char **env);
void				sort_export(char **arr);
int					cd_args_checker(t_command *command,
						t_environment *environment,
						t_gen_list_iter **it);
int					cd_no_args(char *old_pwd, t_environment *environment);
int					check_option_of_export_end(char **new_variable,
						t_environment *env);
int					check_option_of_export(char **var_name, t_environment *env);
int					checker_export_loop(char *arg);

#endif