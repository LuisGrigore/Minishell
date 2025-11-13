/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:07:05 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 17:35:10 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "../external/libft/libft.h"
# include "../include/command.h"
# include "../include/lexer.h"
# include "../include/parser.h"
# include <stdlib.h>

t_command	*handle_command_token(t_token *tok, t_command *current_cmd);
t_command	*handle_arg_token(t_token *tok, t_command *current_cmd);
t_command	*handle_redirect(t_token *tok, t_token *file_tok,
				t_command *current_cmd);
int			handle_pipe_token(t_command *current_cmd, t_gen_list *commands);

#endif