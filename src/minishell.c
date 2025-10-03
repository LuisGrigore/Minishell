/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:56:27 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/03 18:10:41 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/executer.h"
#include "include/environment.h"
#include "include/signal_manager.h"
#include "include/history_manager.h"
# include "external/gen_list/gen_list.h"
#include "external/libft/libft.h"

#include "readline/readline.h"
#include <stdbool.h>


char	*get_line_tag(t_gen_list *env)
{
	char	*username;
	char	*line_tag;

	username = env_get(env, "LOGNAME");
	if (!username)
		return (ft_strdup("minishell%"));
	line_tag = ft_strjoin(username, "%>$");
	free(username);
	return (line_tag);
}

int	main(int args, char **environment_var_str_array)
{
	t_gen_list	*envioroment_vars;
	bool		finish;
	char		*line;

	if (args > 1)
		exit(0);
	signals_init_interactive();
	envioroment_vars = env_deserialize(environment_var_str_array
			+ 2);
	finish = false;
	while (!finish)
	{
		line = readline(get_line_tag(envioroment_vars));
		if ((ft_strlen(line) != 0 && ft_strncmp(line, "exit",
					ft_strlen(line)) == 0) || line == NULL)
			finish = true;
		else if (ft_strlen(line) != 0)
		{
			history_add(line);
			execute_line(line, envioroment_vars);
		}
		free(line);
		line = NULL;
	}
	env_destroy(envioroment_vars);
}
