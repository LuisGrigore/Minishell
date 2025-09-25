#include "../include/command.h"
#include "../include/command_functs.h"
#include "../include/list.h"
#include "../include/redirect_asignation.h"
#include "../include/util.h"
#include "../libft/libft.h"
#include "stdlib.h"
#include <stdio.h>

static int				last_redirecction_before_string_from_string(char *str);
static int				first_redirection_after_string_from_string(char *str);

static t_command	*init_command(void)
{
	t_command	*new_command;

	new_command = ft_calloc(1, sizeof(t_command));
	new_command->args = NULL;
	new_command->command_funct = NULL;
	new_command->redirects = init_list();
	return (new_command);
}

static t_command_funct	get_command_funct(char *command_name)
{
	if (ft_strncmp(command_name, "cd", 2) == 0)
		return (cd_execute);
	else if (ft_strncmp(command_name, "pwd", 3) == 0)
		return (pwd_execute);
	else if (ft_strncmp(command_name, "export", 6) == 0)
		return (export_execute);
	else if (ft_strncmp(command_name, "unset", 5) == 0)
		return (unset_execute);
	else if (ft_strncmp(command_name, "env", 3) == 0)
		return (env_execute);
	else if (ft_strncmp(command_name, "echo", 4) == 0)
		return (echo_execute);
	else
		return (bin_execute);
}

static t_gen_list	*get_args(char *command_line)
{
	t_gen_list	*args;
	int			i;
	int			j;
	char		*aux;
	char		**aux_aux;

	args = init_list();
	j = first_redirection_after_string_from_string(command_line);
	i = last_redirecction_before_string_from_string(command_line);
	aux = ft_substr(command_line, i, (size_t)j - i);
	aux_aux = ft_split2(aux, ' ');
	i = 0;
	free(aux);
	while (aux_aux[i])
	{
		push_end(args, ft_strdup(aux_aux[i]));
		i++;
	}
	free_double_pointer(aux_aux);
	return (args);
}
static char	*get_command_name(char *str)
{
	int	i;
	int	j;

	i = last_redirecction_before_string_from_string(str);
	while (str[i] && ft_ispace(str[i]))
		i++;
	j = i;
	while (str[j] && !ft_ispace(str[j]))
		j++;
	return (ft_substr(str, i, (size_t)(j - i)));
}

static t_command	*init_command_from_str(char *str)
{
	t_command	*new_command;

	new_command = init_command();
	new_command->args = get_args(str);
	new_command->command_funct = get_command_funct(get_command_name(str));
	new_command->redirects = get_redirects_from_str_arr(str);
	return (new_command);
}

t_gen_list	*get_command_list_from_line(char *line)
{
	t_gen_list	*command_list;
	char		**command_str_arr;
	int			i;

	command_list = init_list();
	i = 0;
	command_str_arr = ft_split2(line, '|');
	while (command_str_arr[i])
	{
		push_end(command_list, init_command_from_str(command_str_arr[i]));
		i++;
	}
	return (command_list);
}

void	destroy_command(void *command_to_delete)
{
	t_command	*command;

	command = (t_command *)command_to_delete;
	if (command->args)
		destroy_gen_list(command->args, free);
	if (command->redirects)
		destroy_gen_list(command->redirects, destroy_redirect);
	;
	free(command);
}
char	**get_str_array_from_gen_list_args(t_gen_list *args)
{
	char	**result;
	t_node	*current_node;
	int		i;

	i = 0;
	result = ft_calloc(args->size + 1, sizeof(char *));
	current_node = args->head;
	while (current_node != NULL)
	{
		result[i] = ft_strdup((char *)current_node->value);
		current_node = current_node->next;
		i++;
	}
	return (result);
}

static int	first_redirection_after_string_from_string(char *str)
{
	int		i;
	char	*aux;

	aux = NULL;
	if (!str)
		return (0);
	i = 0;
	while (str[i] && (str[i] != '<' || str[i] != '>'))
	{
		if (str[i] == 34)
			aux = get_next_argument("\"", str + i);
		else if (str[i] == 39)
			aux = get_next_argument("'", str + i);
		else
			i++;
		if (aux)
		{
			i = aux - str;
			aux = NULL;
		}
	}
	return (i);
}
static int	last_redirecction_before_string_from_string(char *str)
{
	int		i;
	char	*aux;

	i = 0;
	while (str[i])
	{
		while (str[i] && ft_ispace(str[i]))
			i++;
		while (str[i] && !ft_ispace(str[i]))
		{
			if (str[i] != '<' || str[i] != '>')
				break ;
			i++;
		}
		while (str[i] && ft_ispace(str[i]))
			i++;
		while (str[i] && !ft_ispace(str[i]))
		{
			if (str[i] == '"')
			{
				aux = get_next_argument("\"", str + i);
				i = aux - str;
			}
			else if (str[i] == 39)
			{
				aux = get_next_argument("'", str + i);
				i = aux - str;
			}
			else
				i++;
		}
	}
	if (i == (int)ft_strlen(str))
		i = 0;
	return (i);
}

/*
	while(command_line[i] && ft_ispace(command_line[i]))
		i++;

	while(command_line[i] && i < j)
	{   aux = i;
		while (command_line[aux] && !ft_ispace(command_line[aux]))
			aux++;
		insert_end(args, ft_substr(command_line, i, aux));
		i = aux;
		while(command_line[i] && ft_ispace(command_line[i]))
			i++;
	}*/