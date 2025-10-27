/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manger_internal_execution.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:13:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/24 12:05:01 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_manager_internal.h"

static int check_in(char *fd);

static int	check_outfile(char *fd, t_redirect_type type)
{
	int	result;
    
        
	result = open(fd, O_RDONLY);
	if (result >= 0)
	{
        close(result);
        if(type == DOUBLE_RIGHT_REDIRECT)     
            result = open(fd ,O_WRONLY | O_APPEND);
        else   
		    result = open( fd, 1 | O_CREAT | O_TRUNC, 0777);
	}
	if (result == -1)
	{
		if (access(fd, F_OK) != -1)
            return (-1);
		else
		{
			close(result);
			result = open(fd, 1 | O_CREAT | O_TRUNC, 0777);
		}
	}
	return (result);
}

void file_dup(t_redirect *redirect)
{
    int fd;

    if(redirect->redirect_simbol == LEFT_REDIRECT)
    {
        fd = check_in(redirect->file);
        if(fd == -1)
            perror("invalid file please check");
        else
        {
            dup2(fd, STDIN_FILENO);
            return ;
        }
    }
    else
    {
        fd = check_outfile(redirect->file, redirect->redirect_simbol);
        if(fd == -1)
            perror("invalid file please check");
        else
        {
            dup2(fd, STDOUT_FILENO);
            return ;
        }

    }
}
int check_in(char *fd)
{
    int result;
    
    result = open(fd, O_RDWR);
    if(result == -1)
        return(-1);
    return(result);
    
}