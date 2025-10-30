/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_queries.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 04:47:07 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/24 07:48:28 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"

static	size_t back_directory(char *current);
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
char *new_directory(char *current, char *target)
{
	char *joined_path;
	char *temp;

	temp = NULL;
	if(!target || !current)
		return NULL;
	if(ft_strncmp(target, "..", 2) == 0)
	{
		temp = current;
			current = ft_substr(temp, 0, back_directory(temp));
			if(ft_strlen(target) == 2 || (ft_strlen(target)== 3 && target[2] == '/'))
			return (current);
		else
			target = target + 3;

	}
	
	if (ft_strncmp(target, "/", 1) == 0)
		return ft_strdup(target);
	joined_path = ft_strjoin(current, "/");
	if(target[ft_strlen(target) -1] == '/')
		joined_path = ft_strjoin(joined_path, ft_substr(target, 0, ft_strlen(target) -1));
	else
	joined_path = ft_strjoin(joined_path, target);
	return (joined_path);
}
static	size_t back_directory(char *current)
{
	size_t len;

	len = ft_strlen(current);
	while (len > 0 && current[len - 1] != '/')
		len--;
	if (len == 0)
		return (1);
	return (len - 1);
}