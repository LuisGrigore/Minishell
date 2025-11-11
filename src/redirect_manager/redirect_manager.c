#include "readline/readline.h"
#include "redirect_manager_internal.h"
#include <stdio.h>
#include <stdlib.h>

t_redirect	*redirect_create(t_redirect_type redirect_type, char *file_name)
{
	t_redirect	*r;

	r = malloc(sizeof(t_redirect));
	if (!r)
		return (NULL);
	r->symbol = redirect_type;
	if (file_name)
	{
		r->file = malloc(ft_strlen(file_name) + 1);
		if (!r->file)
		{
			free(r);
			return (NULL);
		}
		ft_strlcpy(r->file, file_name, ft_strlen(file_name) + 1);
	}
	else
		r->file = NULL;
	return (r);
}

void	redirect_destroy(t_redirect *redirect)
{
	free(redirect->file);
	free(redirect);
}

static int	heredoc_exec(char *delimiter)
{
	char	*input;
	char	*temp_dir;
	int		fd;

	signals_restore();
	temp_dir = PATH_HEREDOC_TEMP_FILE;
	if (!delimiter)
		return (REDIRECT_NO_HEADERDOC_DELIMITER_ERR);
	fd = open(temp_dir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (MS_OPEN_ERR);
	while (1)
	{
		input = readline(">");
		if (!input || (delimiter && ft_strncmp(input, delimiter,
					ft_strlen(delimiter)) == 0
				&& ft_strlen(delimiter) == ft_strlen(input)))
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	signals_restore();
	close(fd);
	fd = open(temp_dir, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (!input)
		return (REDIRECT_NO_HEADERDOC_DELIMITER_ERR);
	return (MS_OK);
}

static int	file_dup_outfile_redirect(int fd, t_redirect *redirect,
		t_mini_state *mini_state)
{
	if (redirect->symbol == DOUBLE_RIGHT_REDIRECT)
	{
		fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		mini_state_set_last_opened_file(mini_state, redirect->file);
		if (fd < 0)
			return (MS_OPEN_ERR);
		dup2(fd, STDOUT_FILENO);
	}
	else if (redirect->symbol == RIGHT_REDIRECT)
	{
		fd = open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		mini_state_set_last_opened_file(mini_state, redirect->file);
		if (fd < 0)
			return (MS_OPEN_ERR);
		dup2(fd, STDOUT_FILENO);
	}
	return (MS_OK);
}
int	redirect_execute(t_redirect *redirect, t_mini_state *mini_state,
		int stdin_bakup)
{
	int	fd;
	int	status_code;

	if (redirect->symbol == DOUBLE_LEFT_REDIRECT)
	{
		dup2(stdin_bakup, 0);
		return (heredoc_exec(redirect->file));
	}
	if (redirect->file == NULL)
		return (REDIRECT_MALFORMED_ERR);
	if (redirect->symbol == LEFT_REDIRECT)
	{
		fd = open(redirect->file, O_RDONLY);
		mini_state_set_last_opened_file(mini_state, redirect->file);
		if (fd < 0)
			return (MS_OPEN_ERR);
		dup2(fd, STDIN_FILENO);
	}
	status_code = file_dup_outfile_redirect(fd, redirect, mini_state);
	if (status_code != MS_OK)
		return (status_code);
	close(fd);
	return (MS_OK);
}
