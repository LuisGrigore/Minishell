/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_manager_internal.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:command/command_internal.h
/*   Created: 2025/10/01 15:57:13 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/01 20:51:22 by lgrigore         ###   ########.fr       */
=======
/*   Created: 2025/10/03 15:06:50 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/03 17:56:32 by lgrigore         ###   ########.fr       */
>>>>>>> lgrigore:src/signal_manager/signal_manager_internal.h
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MANAGER_INTERNAL_H
#define SIGNAL_MANAGER_INTERNAL_H

#include "../include/signal_manager.h"
#include "readline/readline.h"
#include <signal.h>
#include <unistd.h>

#include "../include/command.h"
#include "../include/environment.h"
#include "../include/util.h"
# include "../external/gen_list/gen_list.h"
#include "../external/libft/libft.h"
# include "include/redirect.h"
#include <signal.h>
#include <stdlib.h>

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
char	*find_command(char **env, char *cmd);

#endif