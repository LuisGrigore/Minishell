/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manager_internal.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:02:03 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/05 19:08:25 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_INTERNAL_H
#define REDIRECT_INTERNAL_H
#include "../include/redirect_manager.h"
# include "../external/libft/libft.h"
# include "ms_status_codes.h"
#include "../config.h"

struct s_redirect
{
	char			*file;
	t_redirect_type	redirect_simbol;
};

int file_dup(t_redirect *redirect);

#endif