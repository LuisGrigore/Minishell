/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manager_internal.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:02:03 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/03 15:37:11 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_INTERNAL_H
#define REDIRECT_INTERNAL_H
#include "../include/redirect_manager.h"
# include "../external/libft/libft.h"
//TODO :: Quitar cuando sea posible.
# include "../external/gen_list/gen_list.h"

struct s_redirect
{
	char			*file;
	t_redirect_type	redirect_simbol;
};

t_gen_list			*get_redirects_from_str_arr(char *str);

#endif