/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_state_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:39:37 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/09 16:01:28 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_STATE_H
#define MINI_STATE_H

#include "../include/mini_state.h"
#include "../include/environment.h"
#include "../external/libft/libft.h"


typedef struct s_mini_state
{
	t_gen_list	*environment_vars;
	char *last_command;
	char *last_opened_file;
	bool exit_after_last_command;
} t_mini_state;



#endif