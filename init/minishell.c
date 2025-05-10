/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:56:27 by dmaestro          #+#    #+#             */
/*   Updated: 2025/05/03 19:56:29 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include "../include/bin_commandss_execution.h"

int main(int args, char **argv, char **env)
{
    t_command *cmd;
    t_envioroment *envioroment;
    pid_t check;
    char *recept;
    char *name;

    name = username(env);
    envioroment = init_env();
    env_to_list(env, envioroment);
    printf("%s\n", argv[args]);
    
    while(1)
    {
        cmd = init_cmd();
        recept = readline(name);
        if(check_cmd(recept) == NULL)
            continue ;
        add_history(recept);
        cmd_assignation(recept, cmd);
        check = fork();
        if(check == 0)    
            exec_command(cmd,envioroment);
        else
              waitpid(check,NULL, 0);
        free(recept);
        recept = NULL;
        command_destroyer(cmd);
        cmd = NULL;
    }
}
