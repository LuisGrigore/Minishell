/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc_manger.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:28:30 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 20:29:53 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline/readline.h"
#include "redirect_manager_internal.h"

static int	heredoc_create_end(char *temp_file, char *input, int fd)
{
	if (temp_file)
		free(temp_file);
	close(fd);
	if (!input)
	{
		if (g_signal == SIGINT)
			return (MS_CNTRL_ERR);
		else
			return (REDIRECT_NO_HEADERDOC_DELIMITER_ERR);
	}
	if (input && *input == '\0')
		return (free(input), MS_CNTRL_ERR);
	if (input)
		free(input);
	return (MS_OK);
}

static int	heredoc_create(char *delimiter, int *i)
{
	char	*input;
	char	*temp_dir;
	int		fd;
	char	*itoa_result;

	*i += 1;
	itoa_result = ft_itoa(*i);
	temp_dir = ft_strjoin(PATH_HEREDOC_TEMP_FILE, itoa_result);
	free(itoa_result);
	signals_init_heredoc();
	if (!delimiter)
		return (REDIRECT_NO_HEADERDOC_DELIMITER_ERR);
	fd = open(temp_dir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (MS_OPEN_ERR);
	while (1)
	{
		input = readline(">");
		if (!input || (delimiter && (ft_strncmp(input, delimiter,
						ft_strlen(input)) == 0) && ft_strlen(input) > 0))
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	signals_init_interactive();
	return (heredoc_create_end(temp_dir, input, fd));
}

int	redirect_heredoc_check(t_gen_list *redirects, t_mini_state *mini_state)
{
	t_gen_list_iter	*it;
	t_redirect		*actual_redirect;
	int				i;
	int				status_code;

	i = 0;
	if (!redirects)
		return (MS_OK);
	it = gen_list_iter_start(redirects);
	if (!it)
		return (MS_ALLOCATION_ERR);
	status_code = MS_OK;
	actual_redirect = gen_list_iter_next(it);
	while (actual_redirect)
	{
		if (actual_redirect->symbol == DOUBLE_LEFT_REDIRECT)
			status_code = heredoc_create(actual_redirect->file, &i);
		actual_redirect = gen_list_iter_next(it);
		if (status_code != MS_OK)
			break ;
	}
	mini_state_set_heredoc_temp_file(mini_state, i);
	gen_list_iter_destroy(it);
	mini_state_set_exit_after_last_command(mini_state, true);
	return (status_code);
}

static int	assignate_temp_file(t_redirect *redirect, int *i)
{
	char	*temp_dir;
	char	*itoa_result;

	if (!redirect)
		return (MS_ALLOCATION_ERR);
	*i += 1;
	itoa_result = ft_itoa(*i);
	temp_dir = ft_strjoin(PATH_HEREDOC_TEMP_FILE, itoa_result);
	free(itoa_result);
	free(redirect->file);
	redirect->file = temp_dir;
	return (MS_OK);
}

int	redirect_heredoc_asignate(t_gen_list *redirects, t_mini_state *mini_state)
{
	t_gen_list_iter	*it;
	t_redirect		*actual_redirect;
	int				i;
	int				status_code;

	i = 0;
	if (!redirects)
		return (MS_OK);
	it = gen_list_iter_start(redirects);
	if (!it)
		return (MS_ALLOCATION_ERR);
	actual_redirect = gen_list_iter_next(it);
	status_code = MS_OK;
	while (actual_redirect)
	{
		if (actual_redirect->symbol == DOUBLE_LEFT_REDIRECT)
			status_code = assignate_temp_file(actual_redirect, &i);
		actual_redirect = gen_list_iter_next(it);
		if (status_code != MS_OK)
			break ;
	}
	mini_state_set_heredoc_temp_file(mini_state, i);
	gen_list_iter_destroy(it);
	return (status_code);
}
