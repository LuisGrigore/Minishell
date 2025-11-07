/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_state.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:39:37 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/07 16:47:51 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_STATE_H
#define MINI_STATE_H

#include "../external/gen_list/gen_list.h"

typedef struct s_mini_state t_mini_state;

t_mini_state *mini_state_create(int args, char **environment_var_str_array);
void mini_state_destroy(t_mini_state *state);
char *mini_state_get_last_command(t_mini_state *state);
char *mini_state_get_last_opened_file(t_mini_state *state);
t_gen_list *mini_state_get_environment_vars(t_mini_state *state);
void mini_state_set_last_command(t_mini_state *state, const char *command);
void mini_state_set_last_opened_file(t_mini_state *state, const char *file_name);

#endif