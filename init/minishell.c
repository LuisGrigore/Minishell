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


#include "../include/list.h"
#include "../include/command.h"
#include "../include/bin_commandss_execution.h"
#include "../include/envioroment.h"
#include "../libft/libft.h"
#include "../include/pipe.h"
#include <stdbool.h>

static char *history_checker(char *cmd)
{
    int i;

    i = 0;
    if(cmd[0] == '|' || cmd[ft_strlen(cmd)] == '|')
     {
        add_history(cmd);
        return(NULL);
     }

     while(cmd[i])
     {
        if(ft_ispace(cmd[i]) == 0)
                break;
        i++;
     }
     if(cmd[i] == '\0')
        return(NULL);
     return(cmd);
}

char *check_cmd(char *cmd)
{
    int i;
    int b;

    b = 0;
    i = 0;
    if(history_checker(cmd) == NULL)
        return(NULL);
    while (cmd[i])
    {
        if (cmd [i] == '"' )
            b = 1;
        i++;
        while (cmd[i] && b == 1)
        {
            if(cmd[i] == '"')
                b = 0;
            i++;
        }   
    }
    if(b != 0)
    {
        add_history(cmd);
        return(NULL);
    }
    return(cmd);
}

char *username(t_gen_list *env)
{
    char *username = get_var_value_from_name(env, "LOGNAME=");

    if(!username)
        return(ft_strdup("minishell%"));

    return(ft_strjoin(username, "%>$"));
}

int main(int args, char **environment_var_str_array)
{
    t_gen_list *current_command_list;
    t_command *current_commad;
    t_gen_list *envioroment_vars;

    bool exit = false;

    char *line;
    char *name;

    
    envioroment_vars = get_environment_var_list_from_str_array(environment_var_str_array);
    name = username(envioroment_vars);
    
    while(!exit)
    {
        line = readline(name);
        if (ft_strncmp(line, "exit", ft_strlen(line)) != 0)
        {
            current_command_list = get_command_list_from_line(line);
            if(check_cmd(line) == NULL)
                continue ;
            add_history(line);
            command_execution(current_command_list, envioroment_vars);
           
        }
        else
            exit = true;
        free(line);
        line = NULL;
        destroy_gen_list(current_command_list, destroy_command);
        current_command_list = NULL;
    }
    destroy_gen_list(envioroment_vars, destroy_envioroment_var);
}
