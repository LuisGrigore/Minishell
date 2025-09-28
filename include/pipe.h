/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:50 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/28 23:15:36 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include "../include/command_functs.h"
# include "fcntl.h"
# include "sys/wait.h"
# include "unistd.h"

void	command_execution(t_gen_list *command, t_gen_list *envioroment);
void execute_commands_with_pipes(t_gen_list *commands, t_gen_list *env);

#endif
