#include "../include/command.h"
#include "../include/util.h"
#include "../include/list.h"
#include "../include/redirect.h"
#include "../include/command_functs.h"
#include "../libft/libft.h"
#include "stdlib.h"
#include <stdio.h>


static t_command *init_command()
{
    t_command *new_command;

    new_command = ft_calloc(1, sizeof(t_command ));
    new_command->args = NULL;
    new_command->command_funct = NULL;
    new_command->redirects = init_list();

    return(new_command);
}

static t_command_funct *get_command_funct(char *command_name)
{
    size_t len;

    len = ft_strlen(command_name)-1;
    //Hay que hacer un if else para cada command_funct
    if(ft_strncmp(command_name, "cd", len) == 0)
        return NULL;
    else if(ft_strncmp(command_name, "pwd", len) == 0)
        return NULL;
    else
        return NULL;
}

static t_gen_list *get_args(char *command_line)
{
    t_gen_list *args = init_list();
    int i = 0;
    int j = 0;

    while(command_line[i] != ' ' && command_line[i] != '<' && command_line[i] != '>')
    {
        i ++;
    }
    if(command_line[i] != ' ')
        return (args);
    
    i ++;
    j =  i;
    while(command_line[i] && command_line[i] != '<' && command_line[i] != '>')
    {
        while (command_line[i] != ' ')
        {
            j++;
        }
        insert_end(args, ft_substr(command_line, i, j));
        i = j;
    }
    return (args);
}

static char *get_command_name(char *str)
{
    int i = 0; 
    while(str[i] != ' ' && str[i] != '<'&& str[i] != '>')
    {
        str++;
        i ++;
    }
    return (ft_substr(str, 0, i));
}

static t_command *init_command_from_str(char *str)
{
    t_command *new_command = init_command();

    new_command->args = get_args(str);
    new_command->command_funct = get_command_funct(get_command_name(str));
    new_command->redirects = get_redirects_from_str_arr(str);
    return(new_command);
}


t_gen_list *get_command_list_from_line(char *line)
{
    t_gen_list *command_list = init_list();
    char **command_str_arr;
    int i = 0;
    command_str_arr = ft_split2(line, '|');
    while (command_str_arr[i])
    {
        insert_end(command_list, init_command_from_str(command_str_arr[i]));
        i++;
    }
    return (command_list);
}

void destroy_command(t_command *command)
{
    destroy_gen_list(command->args, free);
    free(command->command_funct);
    destroy_gen_list(command->redirects, destroy_redirect);
    free(command);
}
char **get_str_array_from_gen_list_args(t_gen_list *args)
{
    char **result;
    t_node *current_node;
    int i;

    i = 0;    
    result = ft_calloc(args->size, sizeof(char *));
    current_node = args->head;
    while(current_node != NULL)
    {
        result[i] = ft_strdup(current_node->value);
        i++;
    }
    return(result);
}


