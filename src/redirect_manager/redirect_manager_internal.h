/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manager_internal.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:02:03 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/05 20:25:36 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_INTERNAL_H
#define REDIRECT_INTERNAL_H
#include "../include/redirect_manager.h"
# include "../external/libft/libft.h"


struct s_redirect
{
	char			*file;
	t_redirect_type	redirect_simbol;
};

void file_dup(t_redirect *redirect);

#endif