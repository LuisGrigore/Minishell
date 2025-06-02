/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_commandss_execution.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:01 by dmaestro          #+#    #+#             */
/*   Updated: 2025/06/02 18:18:03 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_COMMAND_EXECUTION_H
# define BIN_COMMAND_EXECUTION_H

#include "envioroment.h"
#include "command.h"
#include "util.h"


char	*find_command(char **env, char *cmd);

# endif
