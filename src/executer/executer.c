/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:15:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/30 17:24:08 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_internal.h"

//TODO :: hacer que devuelva int con error y tal
static  int execute_commands_with_pipes(t_gen_list *commands, t_gen_list *env)
{
    size_t n = gen_list_get_size(commands);
    t_pipe_manager *pm = NULL;
    int status_code;
    t_gen_list_iter *it;
    t_command *cmd;
    pid_t *pids;
    size_t i = 0;

    if (n == 0)
        return(GEN_LIST_IS_NULL_ERR);

    pm = pipe_manager_init(n);
    if (!pm)
        return(PIPE_MANAGER_IS_NULL);

    it = gen_list_iter_start(commands);
    if (!it)
        return (pipe_manager_destroy(pm), -1);

    pids = malloc(sizeof(pid_t) * n);
    if (!pids)
        return (gen_list_iter_destroy(it), pipe_manager_destroy(pm), -1);

    while ((cmd = gen_list_iter_next(it)) != NULL)
    {
        pid_t pid = fork();
        if (pid == 0) // hijo
        {
            pipe_manager_setup_command(pm, i);
            pipe_manager_close_all(pm);
            status_code = command_exec(cmd, env);

            if (status_code != MS_OK)
            {   
                free(pids);
                gen_list_iter_destroy(it);
                pipe_manager_destroy(pm);
                return (status_code);
            }
            exit(0);
        }
        else
        {
            pids[i] = pid;
        }
        i++;
    }

    pipe_manager_close_all(pm);

    for (size_t j = 0; j < i; j++)
        waitpid(pids[j], NULL, 0);

    gen_list_iter_destroy(it);
    free(pids);
    pipe_manager_destroy(pm);
	//Borra el archivo temporal despues de haber esperado a los procesos hijos
    unlink(PATH_HEREDOC_TEMP_FILE);
        return(MS_OK);
}

static void command_destroy_data(void *command_ptr)
{
	command_destroy((t_command *) command_ptr);
}

/*static int handle_parser_errors(int status_code)
{
	return(MS_OK);
}*/

int execute_line(char *line, t_gen_list *env)
{
	int status_code;
	t_gen_list *commands;


	commands = gen_list_create();
	if (!commands)
		return (MS_ALLOCATION_ERR);
	status_code = parse_line(line, commands);
	if(status_code != MS_OK)
		return (EXECUTER_ERR);
	if (gen_list_get_size(commands) == 1 && command_is_built_in((t_command *) gen_list_peek_top(commands)))
	{   
        status_code = command_exec((t_command *) gen_list_peek_top(commands), env);
		if( status_code != MS_OK)
        {
            gen_list_destroy(commands, command_destroy_data);
            return(status_code);   
        }
            
		return(MS_OK);
	}
	status_code = execute_commands_with_pipes(commands, env);
	gen_list_destroy(commands, command_destroy_data);
	return (status_code);
}
