/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager_internal.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:38:45 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 00:18:58 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_MANAGER_INTERNAL_H
# define PIPE_MANAGER_INTERNAL_H

# include "../include/pipe_manager.h"
# include <fcntl.h>
# include <unistd.h>

struct		s_pipe_manager
{
	size_t	n_cmds;
	int		(*pipes)[2];
};

#endif