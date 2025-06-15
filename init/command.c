#include "../include/command.h"
#include "../include/util.h"
#include "../include/list.h"
#include "../include/redirect_asignation.h"
#include "../include/command_functs.h"
#include "../libft/libft.h"
#include "stdlib.h"
#include <stdio.h>


static int last_redirecction_before_string_from_string(char *str);
static int first_redirection_after_string_from_string(char *str);

static t_command *init_command()
{
    t_command *new_command;

    new_command = ft_calloc(1, sizeof(t_command ));
    new_command->args = NULL;
    new_command->command_funct = NULL;
    new_command->redirects = init_list();
    new_command->command_name = NULL;

    return(new_command);
}

static t_command_funct get_command_funct(char *command_name)
{
    size_t len;

    len = ft_strlen(command_name)-1;
    if(ft_strncmp(command_name, "cd", len) == 0)
        return (cd_execute);
    else if(ft_strncmp(command_name, "pwd", len) == 0)
        return (pwd_execute);
    else if(ft_strncmp(command_name, "export", len) == 0)
        return (export_execute);
    else if(ft_strncmp(command_name, "unset", len) == 0)
        return (unset_execute);
    else if(ft_strncmp(command_name, "env", len) == 0)
        return (env_execute);
    else if(ft_strncmp(command_name, "echo", len) == 0)
        return (echo_execute);
    else
        return (bin_execute);
}

static t_gen_list *get_args(char *command_line)
{
    t_gen_list *args = init_list();
    int i;
    int j;
    int aux;
    
    j = first_redirection_after_string_from_string(command_line);
    i = last_redirecction_before_string_from_string(command_line);
    
    
    while(command_line[i] && ft_ispace(command_line[i]))
        i++;
    while(command_line[i] && !ft_ispace(command_line[i]))
        i++;
    while(command_line[i] && ft_ispace(command_line[i]))
        i++;
        
    while(command_line[i] && i < j)
    {   aux = i;
        while (command_line[i] && !ft_ispace(command_line[aux]))
            aux++;    
        insert_end(args, ft_substr(command_line, i, aux));
        i = aux;
        while(command_line[i] && ft_ispace(command_line[i]))
            i++;
    }
    return (args);
}
static char *get_command_name(char *str)
{
    int i;
    int j;

    i = last_redirecction_before_string_from_string(str);
    while(str[i]  && ft_ispace(str[i]))
        i++;
    j = i;
    while(str[j] && !ft_ispace(str[j]))
        j++;
    return(ft_substr(str, i, (size_t)(j - i)));
    

}

static t_command *init_command_from_str(char *str)
{
    t_command *new_command = init_command();

    new_command->args = get_args(str);
    new_command->command_name = get_command_name(str);
    new_command->command_funct = get_command_funct(new_command->command_name);
    new_command->redirects = get_redirects_from_str_arr(str);
    return(new_command);
}


t_gen_list *get_command_list_from_line(char *line)
{
    t_gen_list *command_list = init_list();
    char **command_str_arr;
    int i = 0;
    command_str_arr = ft_split2(line, '|');
    while(command_str_arr[i])
        i++;
    i--;
    while (i >= 0)
    {
        insert_end(command_list, init_command_from_str(command_str_arr[i]));
        i--;
    }
    return (command_list);
}

void destroy_command(void *command_to_delete)
{
    t_command *command;
    command = (t_command *)command_to_delete;
    if(command->args)
        destroy_gen_list(command->args, free);
    if(command->redirects)
        destroy_gen_list(command->redirects, destroy_redirect);
    if(command->command_name)
        free(command->command_name);
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

static int first_redirection_after_string_from_string(char *str)
{
    int i;
    char *aux;
    
    aux = NULL;
    if(!str)
        return(0);
    i = 0;
    while(str[i] && (str[i] != '<' || str[i] != '>'))
    {
        if(str[i] ==  34)
            aux = get_next_argument("\"", str + i);
        else if(str[i] ==  39)    
            aux = get_next_argument("'", str + i);
        else
            i++;
        if(aux)
        {
            i = aux - str;
            aux = NULL;
        }
    }
    return(i);
}
static int last_redirecction_before_string_from_string(char *str)
{
    int i;
    char *aux;

    i = 0;
    while(str[i])
    {
        while(str[i] && ft_ispace(str[i]))
            i++;
        while(str[i] && !ft_ispace(str[i]))
        {
            if(str[i] != '<' || str[i] != '>')
                break;
            i++;  
        }
        while (str[i] && ft_ispace(str[i]))
            i++;
        while( str[i] && !ft_ispace(str[i]))
        {
          if(str[i] == '"' )
            {
                aux = get_next_argument("\"", str + i);
                i = aux - str;
            }
          else if(str[i] != 39)
            {
                aux = get_next_argument("'", str + i);
                i = aux - str;
            }
            else
                i++;  
        }
    }
    if(i == (int)ft_strlen(str))
        i = 0;    
    return(i);
    
}


