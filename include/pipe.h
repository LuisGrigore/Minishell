/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:50 by dmaestro          #+#    #+#             */
/*   Updated: 2025/06/02 18:18:52 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include "../include/command_functs.h"
# include "fcntl.h"
# include "sys/wait.h"
# include "unistd.h"

void	command_execution(t_gen_list *command, t_gen_list *envioroment);

#endif
