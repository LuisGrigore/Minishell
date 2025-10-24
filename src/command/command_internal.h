/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:57:13 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/24 04:45:51 by dmaestro         ###   ########.fr       */
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

typedef void				(*t_command_funct)(t_command *, t_gen_list *);

struct s_command
{
	t_gen_list		*args;
	t_gen_list		*redirects;
	bool			is_builtin;
	t_command_funct	command_funct;
};


void						pwd_execute(t_command *command,
								t_gen_list *envioroment);
void						bin_execute(t_command *cmd,
								t_gen_list *envioroment);
void						cd_execute(t_command *command,
								t_gen_list *envioroment);
void						pwd_execute(t_command *command,
								t_gen_list *envioroment);
void						export_execute(t_command *command,
								t_gen_list *envioroment);
void						unset_execute(t_command *command,
								t_gen_list *envioroment);
void						env_execute(t_command *command,
								t_gen_list *envioroment);
void						echo_execute(t_command *command,
								t_gen_list *envioroment);
char 						*new_directory(char *current, char *target);
								

#endif