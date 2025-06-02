/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:21 by dmaestro          #+#    #+#             */
/*   Updated: 2025/06/02 18:18:23 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "envioroment.h"

typedef  void (*t_command_funct)(t_command *, t_gen_list *);

void pwd_execute(t_command *command, t_gen_list *envioroment);
void	bin_execute(t_command *cmd ,t_gen_list *envioroment);
void    cd_execute(t_command *command,t_gen_list *envioroment);
void pwd_execute(t_command *command, t_gen_list *envioroment);
void export_execute(t_command *command, t_gen_list *envioroment);
void unset_execute(t_command *command, t_gen_list *envioroment);
void env_execute(t_command *command, t_gen_list *envioroment);
void echo_execute(t_command *command, t_gen_list *envioroment);
