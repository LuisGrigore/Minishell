/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:19:19 by dmaestro          #+#    #+#             */
/*   Updated: 2025/06/02 18:19:21 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

char	**ft_split2(char const *s, char c);
int ft_ispace(char c);
int special_char(char *str, char *c);
char *get_next_argument(char *c, char *str);

#endif
