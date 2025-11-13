/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_manager_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:46:57 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/13 01:42:47 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "signal_manager_internal.h"

int	signals_restore(void)
{
	t_ms_status_code	ret;

	ret = set_signal(SIGINT, SIG_DFL);
	if (ret != MS_OK)
		return (ret);
	ret = set_signal(SIGQUIT, SIG_DFL);
	return (ret);
}
