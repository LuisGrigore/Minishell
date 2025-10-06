/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_status_codes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:19:01 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/06 14:34:17 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERRORS_H
#define MS_ERRORS_H

#define SYSTEM_STATUS_BEGIN 0

typedef enum e_ms_status_code
{
	MS_OK = SYSTEM_STATUS_BEGIN,
	MS_ERR_FORK,
	MS_ERR_PIPE,
	MS_DUP2_ERR,
	MS_MALLOC_ERR,
	MS_CLOSE_ERR,
	MS_SIGNAL_ERR,
	MS_ERR_FILE,

} t_ms_status_code;

#endif