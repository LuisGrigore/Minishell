/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manger_internal_execution.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:13:16 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/05 17:09:30 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_manager_internal.h"

static int check_in(char *fd);

static int	check_outfile(char *fd, t_redirect_type type)
{
	int	result;
    
    if(!fd)
        return(REDIRECT_MANAGER_ERR_SYNTAX);       
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
            return (REDIRECT_MANAGER_ERR_INVALID_FD);
		else
		{
			close(result);
			result = open(fd, 1 | O_CREAT | O_TRUNC, 0777);
		}
	}
	return (result);
}

int file_dup(t_redirect *redirect)
{
    int fd;

    if(redirect->redirect_simbol == LEFT_REDIRECT)
    {
        fd = check_in(redirect->file);
        if(fd > 800)
            return(fd);
        else
        {
            dup2(fd, STDIN_FILENO);
            return(REDIRECT_MANAGER_SUCCESS) ;
        }
    }
    else
    {
        fd = check_outfile(redirect->file, redirect->redirect_simbol);
        if(fd > 800)
            return(fd);
        else
        {
            dup2(fd, STDOUT_FILENO);
            return(REDIRECT_MANAGER_SUCCESS);
        }

    }
}

int check_in(char *fd)
{
    int result;
    
    if(!fd)
        return(REDIRECT_MANAGER_ERR_INVALID_FD);   

    result = open(fd, O_RDWR);
    if(result == -1)
        return(REDIRECT_MANAGER_ERR_INVALID_FD);
    return(result);
    
}
int redirect_error_control(t_gen_list *list, int(*func)(void *))
{
	t_gen_list_iter	*it;
	void			*val;
    int status_code;

	if (!list || !func)
		return (GEN_LIST_IS_NULL_ERR);
	it = gen_list_iter_start(list);
	if (!it)
		return (GEN_LIST_MALLOC_ERR);
	val = gen_list_iter_next(it);
	while (val)
	{
		status_code = func(val);
        if(status_code != REDIRECT_MANAGER_SUCCESS)
        {
            gen_list_iter_destroy(it);
            return (status_code);
        }
		val = gen_list_iter_next(it);
	}
	gen_list_iter_destroy(it);
	return (MS_OK);
}