/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:11 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/28 18:30:49 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include "command_functs.h"
# include "envioroment.h"
# include "redirect_asignation.h"

typedef struct s_command
{
	t_gen_list		*args;
	t_gen_list		*redirects;
	t_command_funct	command_funct;
}					t_command;

t_command	*init_command(t_gen_list *args, t_command_funct funct,
		t_gen_list *redirects);
t_gen_list			*get_command_list_from_line(char *line);
void				destroy_command(void *command_to_delete);
char				**get_str_array_from_gen_list_args(t_gen_list *args);

#endif
