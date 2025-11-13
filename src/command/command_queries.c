/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_queries.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 04:47:07 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 20:13:33 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"

bool	command_is_built_in(t_command *command)
{
	if (!command)
		return (false);
	return (command->is_builtin);
}

char	*command_get_name(t_command *command)
{
	if (!command || gen_list_is_empty(command->args))
		return (NULL);
	return ((char *)gen_list_peek_top(command->args));
}

 void	sort_export(char **arr)
{
	int		i;
	char	*temp;
	int		n;
	int		j;

	i = 0;
	n = 0;
	while (arr[n])
		n++;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strncmp(arr[j], arr[j + 1], ft_strlen(arr[j])) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	double_pontier_free(char **env)
{
	if (env[1])
		free(env[1]);
	free(env[0]);
	free(env);
}
