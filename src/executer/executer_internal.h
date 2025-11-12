/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 03:23:52 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/12 10:49:35 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_INTERNAL_H
# define EXECUTER_INTERNAL_H

# include "../config.h"
# include "../external/gen_list/gen_list.h"
# include "../external/libft/libft.h"
# include "../include/command.h"
# include "../include/environment.h"
# include "../include/executer.h"
# include "../include/parser.h"
# include "../include/pipe_manager.h"
# include "../include/redirect_manager.h"
# include <sys/wait.h>
# include <unistd.h>

int	execute_with_pipes(t_gen_list *commands, t_mini_state *mini_state,
		int *exit_status);
#endif