/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_manager_internal.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:06:50 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/12 21:20:04 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MANAGER_INTERNAL_H
# define SIGNAL_MANAGER_INTERNAL_H

# include "../include/signal_manager.h"
# include "readline/readline.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	set_signal(int sig, void (*handler)(int));
#endif