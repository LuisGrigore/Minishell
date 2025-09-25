/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:11 by dmaestro          #+#    #+#             */
/*   Updated: 2025/06/16 14:16:23 by dmaestro         ###   ########.fr       */
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

t_gen_list			*get_command_list_from_line(char *line);
void				destroy_command(void *command_to_delete);
char				**get_str_array_from_gen_list_args(t_gen_list *args);

#endif
