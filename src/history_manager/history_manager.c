#include "history_manager_internal.h"

static char	*history_checker(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '|' || cmd[ft_strlen(cmd)] == '|')
	{
		add_history(cmd);
		return (NULL);
	}
	while (cmd[i])
	{
		if (ft_ispace(cmd[i]) == 0)
			break ;
		i++;
	}
	if (cmd[i] == '\0')
		return (NULL);
	return (cmd);
}

static char	*check_cmd(char *cmd)
{
	int	i;
	int	b;

	b = 0;
	i = 0;
	if (history_checker(cmd) == NULL)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '"')
			b = 1;
		i++;
		while (cmd[i] && b == 1)
		{
			if (cmd[i] == '"')
				b = 0;
			i++;
		}
	}
	if (b != 0)
	{
		add_history(cmd);
		return (NULL);
	}
	return (cmd);
}

bool history_add(char *line)
{
	if (check_cmd(line) == NULL)
		return (false);
	add_history(line);
	return (true);
}