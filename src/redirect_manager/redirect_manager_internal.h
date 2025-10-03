/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manager_internal.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:02:03 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/03 19:41:39 by lgrigore         ###   ########.fr       */
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

#endif