/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:07:05 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 04:16:25 by dmaestro         ###   ########.fr       */
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
int			process_token(t_token *tok, t_gen_list_iter *it,
				t_gen_list *commands, t_command **cmd);
int			push_finished_cmd(t_command *cmd, t_gen_list *commands);
#endif
