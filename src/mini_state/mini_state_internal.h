/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_state_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:39:37 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 11:47:16 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_STATE_INTERNAL_H
# define MINI_STATE_INTERNAL_H

# include "../external/libft/libft.h"
# include "../include/environment.h"
# include "../include/mini_state.h"

typedef struct s_mini_state
{
	t_environment	*environment_vars;
	char			*last_command;
	char			*last_opened_file;
	bool			exit_after_last_command;
	int				heredoc_temp_files;
}					t_mini_state;

#endif