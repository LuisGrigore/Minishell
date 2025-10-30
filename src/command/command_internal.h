/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:57:13 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/28 18:25:01 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_INTERNAL_H
#define COMMAND_INTERNAL_H

#include "../include/command.h"
#include "../include/environment.h"
#include "../include/util.h"
#include "../include/signal_manager.h"
# include "../external/gen_list/gen_list.h"
#include "../external/libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>

typedef int				(*t_command_funct)(t_command *, t_gen_list *);

struct s_command
{
	t_gen_list		*args;
	t_gen_list		*redirects;
	bool			is_builtin;
	t_command_funct	command_funct;
};


int						pwd_execute(t_command *command,
								t_gen_list *envioroment);
int						bin_execute(t_command *cmd,
								t_gen_list *envioroment);
int						cd_execute(t_command *command,
								t_gen_list *envioroment);
int						pwd_execute(t_command *command,
								t_gen_list *envioroment);
int						export_execute(t_command *command,
								t_gen_list *envioroment);
int						unset_execute(t_command *command,
								t_gen_list *envioroment);
int						env_execute(t_command *command,
								t_gen_list *envioroment);
int						echo_execute(t_command *command,
								t_gen_list *envioroment);
char 						*new_directory(char *current, char *target);
								

#endif