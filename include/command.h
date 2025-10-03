/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:11 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/01 20:36:14 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include "../external/gen_list/gen_list.h"

/**
 * @file command.h
 * @brief Module that contains the necesary functionality to create and execute commands.
 */

typedef struct s_command	t_command;

typedef void				(*t_command_funct)(t_command *, t_gen_list *);

struct s_command
{
	t_gen_list		*args;
	t_gen_list		*redirects;
	t_command_funct	command_funct;
};

//Command constructor and descructor
t_command	*init_command(t_gen_list *args, t_command_funct funct,
		t_gen_list *redirects);
void				destroy_command(void *command_to_delete);

//COMAND FUNCTIONS



//COMMAND EXECUTIONER
/**
 * @brief Executes the commands in the given list in order as child processes linking their input and output with the corresponding pipes.
 *
 * @param commands Command list to execute
 * @param env Environment variable list that the commands may need.
 */
void execute_commands_with_pipes(t_gen_list *commands, t_gen_list *env);

t_command_funct get_command_function(char *cmd_name);


#endif
