/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:17:24 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 13:18:01 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	file_dup_outfile_redirect(int fd, t_redirect *redirect)
{
	if (redirect->symbol == DOUBLE_RIGHT_REDIRECT)
	{
		fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (MS_OPEN_ERR);
		dup2(fd, STDOUT_FILENO);
	}
	else if (redirect->symbol == RIGHT_REDIRECT)
	{
		fd = open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (MS_OPEN_ERR);
		dup2(fd, STDOUT_FILENO);
	}
	return (MS_OK);
}

int	redirect_execute(t_redirect *redirect, t_mini_state *mini_state)
{
	int	fd;
	int	status_code;

	fd = -1;
	if (redirect->file == NULL)
		return (REDIRECT_MALFORMED_ERR);
	mini_state_set_last_opened_file(mini_state, redirect->file);
	if (redirect->symbol == LEFT_REDIRECT
		|| redirect->symbol == DOUBLE_LEFT_REDIRECT)
	{
		fd = open(redirect->file, O_RDONLY);
		if (fd < 0)
			return (MS_OPEN_ERR);
		dup2(fd, STDIN_FILENO);
	}
	status_code = file_dup_outfile_redirect(fd, redirect);
	if (status_code != MS_OK)
		return (status_code);
	close(fd);
	return (MS_OK);
}


void	print_redirect(void *redir_ptr)
{
	t_redirect *redir = (t_redirect *)redir_ptr;
	if (!redir)
		return ;
	const char *type_str;
	switch (redir->symbol)
	{
	case LEFT_REDIRECT:
		type_str = "<";
		break ;
	case RIGHT_REDIRECT:
		type_str = ">";
		break ;
	case DOUBLE_LEFT_REDIRECT:
		type_str = "<<";
		break ;
	case DOUBLE_RIGHT_REDIRECT:
		type_str = ">>";
		break ;
	default:
		type_str = "UNKNOWN";
		break ;
	}
	printf("    Redirect: %s %s\n", type_str, redir->file);
}