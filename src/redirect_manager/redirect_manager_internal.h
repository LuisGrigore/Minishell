/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manager_internal.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:02:03 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/11 18:21:29 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_INTERNAL_H
# define REDIRECT_INTERNAL_H
# include "../config.h"
# include "../external/libft/libft.h"
# include "../include/redirect_manager.h"
# include "../include/signal_manager.h"
# include "ms_status_codes.h"

struct				s_redirect
{
	char			*file;
	t_redirect_type	symbol;
};

#endif