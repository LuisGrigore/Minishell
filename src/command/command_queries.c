/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_queries.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 04:47:07 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/06 18:15:45 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"

bool command_is_built_in(t_command *command)
{
	if (!command)
		return false;
	return command->is_builtin;
}

char *command_get_name(t_command *command)
{
	if (!command)
		return NULL;
	return ((char *)gen_list_peek_top(command->args));
}
int check_option_of_export(char **new_variable, t_gen_list *env)
{
	char *temp;
	int i;
	char *temp2;

	i = 0;
	while(new_variable[0][i])
	{
		if(!ft_isalnum(new_variable[0][i]))
		{
			if(new_variable[0][i] != '+' || i != ft_strlen(new_variable[0]) - 1)
				return(-1);
			else
				break;
		}
		i++;
		if(!new_variable[0][i])
			return(0);
	}
	temp = ft_substr(new_variable[0],0, ft_strlen(new_variable[0]) - 1);
	free(new_variable[0]);
	new_variable[0] = temp;
	temp = env_get(env, new_variable[0]);
	if(!temp)
		return(0);
	temp2 = new_variable[1];
	new_variable[1] = ft_strjoin(temp, temp2);
	return(free(temp), free(temp2), 0);
}
