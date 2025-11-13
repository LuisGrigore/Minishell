/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:07:05 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/13 21:03:15 by lgrigore         ###   ########.fr       */
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
int			handle_redir_wrapper(t_token *tok, t_gen_list_iter *it,
				t_command **cmd);
int			handle_word_or_arg(t_token *tok, t_command **cmd);
int			push_finished_cmd(t_command *cmd, t_gen_list *commands);
bool		check_status_command_token(int status, t_command *cmd,
				t_token *tok);

#endif