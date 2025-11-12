/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_status_code_internal.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:13:27 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/12 15:46:27 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_STATUS_CODE_INTERNAL_H
# define HANDLE_STATUS_CODE_INTERNAL_H
# include "../external/libft/libft.h"
# include "../include/handle_status_code.h"
# include "../include/history_manager.h"
# include "../include/ms_status_codes.h"
# include "string.h"
# include <errno.h>

void	handle_command_status_codes(int status, t_mini_state *mini_state);
void	select_function_to_handle(int status_code, t_mini_state *mini_state);
void	handle_system_status_codes(int status_code, t_mini_state *mini_state);
void	handle_status_codes(int status_code, t_mini_state *mini_state,
			char *input);

#endif