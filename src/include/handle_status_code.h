/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_status_code.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:31:29 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/12 16:36:39 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_STATUS_CODE_H
# define HANDLE_STATUS_CODE_H

# include "mini_state.h"

void	handle_status_codes(int status_code, t_mini_state *mini_state,
			char *input);

#endif