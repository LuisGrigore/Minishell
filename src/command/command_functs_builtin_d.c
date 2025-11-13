/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functs_builtin_d.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:39:58 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 20:40:22 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_internal.h"

int	check_option_of_export_end(char **new_variable, t_environment *env)
{
	char	*temp2;
	char	*temp;

	temp = ft_substr(new_variable[0], 0, ft_strlen(new_variable[0]) - 1);
	free(new_variable[0]);
	new_variable[0] = temp;
	temp = env_get(env, new_variable[0]);
	if (!temp)
		return (0);
	temp2 = new_variable[1];
	new_variable[1] = ft_strjoin(temp, temp2);
	return (free(temp), free(temp2), 0);
}

int	check_option_of_export(char **var_name, t_environment *env)
{
	int	i;

	i = 0;
	while (var_name[0][i])
	{
		if (!ft_isalnum(var_name[0][i]))
		{
			if (var_name[0][i] != '+' || i != (int)ft_strlen(var_name[0]) - 1)
				return (-1);
			else
				break ;
		}
		i++;
		if (!var_name[0][i])
			return (0);
	}
	return (check_option_of_export_end(var_name, env));
}

int	checker_export_loop(char *arg)
{
	if (ft_isdigit(arg[0]))
		return (COMMAND_MALFORMED_ERR);
	if (ft_strlen(arg) == 1 && arg[0] == '=')
		return (COMMAND_MALFORMED_ERR);
	return (MS_OK);
}
