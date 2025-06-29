/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:15:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/06/02 18:15:18 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipe.h"
#include "../libft/libft.h"

static void	children(int *pipes, t_command *command, t_gen_list *envioroment);
static void	partent(int *pipes, t_command *command, t_gen_list *envioroment);
static int cmd_env_change(t_command *current_command_node);

void command_execution(t_gen_list *command, t_gen_list *envioroment)
{
    int pipes[2];
    t_node *current_command_node;
    pid_t check[command->size];
    int  i;
    t_command *current_command;

    i = 0;
    current_command_node = command->head;
    pipe(pipes);
    while (current_command_node->next != NULL)
        {
            current_command = (t_command*) current_command_node->value;
        	if(cmd_env_change(current_command) == 0)
				check[i] = fork();
        	if(check[i] == 0)
                children(pipes, current_command, envioroment);
            current_command_node = current_command_node->next;
            i++;
        }

    if(cmd_env_change(current_command) == 0)
		check[i] = fork();
    if(check[i] == 0)
        partent(pipes, current_command, envioroment);
    while(i >= 0)
    {	if(check[i] != 0)
			waitpid(check[i], NULL, 0);
        i--;
    }
    close(pipes[0]);
    close(pipes[1]);
     
}
static void	children(int *pipes, t_command *command, t_gen_list *envioroment)
{
	/*int	fd;
	if(ok == 2)
		fd = open(argv[1], 0);
	else
		fd = STDIN_FILENO;*/
	/*if (fd == -1)
	{
		close(pipes[0]);
		close(pipes[1]);
		error_manager(NULL, "Check the privilegies of the  input file", 0);
	}*/
	dup2(pipes[1], 1);
	/*close(fd);*/
	close(pipes[0]);
	close(pipes[1]);
    command->command_funct(command, envioroment);
	exit(0);
}
static void	partent(int *pipes, t_command *command, t_gen_list *envioroment)
{
	/*int	fd;*/
	/*if(ok == 2)
		fd = open(argv[1], 0);
	else
		fd = STDIN_FILENO;*/
	/*if (fd == -1)
	{
		close(pipes[0]);
		close(pipes[1]);
		error_manager(NULL, "Check the privilegies of the  input file", 0);
	}*/
	dup2(pipes[0], 0);
	/*close(fd);*/
	close(pipes[0]);
	close(pipes[1]);
    command->command_funct(command, envioroment);
	exit(0);
}
static int cmd_env_change(t_command *current_command_node)
{
	size_t len;
	len = ft_strlen(current_command_node->command_name);
	if(ft_strncmp(current_command_node->command_name, "cd", len) == 0)
        return (1);
    else if(ft_strncmp(current_command_node->command_name, "export", len) == 0)
        return (1);
    else if(ft_strncmp(current_command_node->command_name, "unset", len) == 0)
        return (1);
    else
        return (0);
}
