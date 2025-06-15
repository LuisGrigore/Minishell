/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:11 by dmaestro          #+#    #+#             */
/*   Updated: 2025/06/02 18:18:12 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include "redirect_asignation.h"
# include "envioroment.h"
# include "command_functs.h"



typedef struct s_command
{
    t_gen_list *args;
    t_gen_list   *redirects;
    char *command_name;
    t_command_funct command_funct;
}   t_command;

t_gen_list *get_command_list_from_line(char *line);
void destroy_command(void *command_to_delete);
char **get_str_array_from_gen_list_args(t_gen_list *args);



#endif
