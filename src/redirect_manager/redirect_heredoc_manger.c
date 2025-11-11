/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc_manger.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:28:30 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/11 20:30:56 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_manager_internal.h"
#include "readline/readline.h"

static int	heredoc_create(t_redirect *redirect, char *delimiter, int *i)
{
	char	*input;
	char	*temp_dir;
	int		fd;

    *i += 1;
	temp_dir = ft_strjoin(PATH_HEREDOC_TEMP_FILE, ft_itoa(*i));
	if (!delimiter)
		return REDIRECT_NO_HEADERDOC_DELIMITER_ERR;
	fd = open(temp_dir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return MS_OPEN_ERR;
	while (1)
	{
		input = readline(">");
		if (!input || (delimiter && ft_strncmp(input, delimiter,
					ft_strlen(input)) == 0))
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
    close(fd);
	free(redirect->file);
	redirect->file = temp_dir;
    if (!input)
		return (REDIRECT_NO_HEADERDOC_DELIMITER_ERR);
	return (MS_OK);
}

int redirect_heredoc_check(t_gen_list *redirects, t_mini_state *mini_state)
{
    t_gen_list_iter *it;
    t_redirect  *actual_redirect;
    int i;
    int status_code;
    
    i = 0;
    status_code = MS_OK;
    it = gen_list_iter_start(redirects);
    actual_redirect = gen_list_iter_next(it);
    while(actual_redirect)
    {
        if(actual_redirect->symbol == DOUBLE_LEFT_REDIRECT)
           status_code = heredoc_create(actual_redirect, actual_redirect->file, &i);
        actual_redirect = gen_list_iter_next(it);
        if(status_code != MS_OK)
            break ;        
    }
    mini_state_set_heredoc_temp_file(mini_state, i);
    gen_list_iter_destroy(it);
    return(status_code);
}
