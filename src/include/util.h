/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:19:19 by dmaestro          #+#    #+#             */
/*   Updated: 2025/11/09 23:26:50 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

/**
 * @brief Enhanced string split that handles quoted sections
 *
 * Similar to ft_split but preserves text within quotes as a single token.
 *
 * @param s String to split
 * @param c Delimiter character
 * @return Array of strings, NULL-terminated, or NULL on error
 */
char	**ft_split2(char const *s, char c);

/**
 * @brief Checks if a character is whitespace
 *
 * Tests for space, tab, newline, carriage return, etc.
 *
 * @param c Character to test
 * @return 1 if whitespace, 0 otherwise
 */
int		ft_ispace(char c);

/**
 * @brief Checks for special shell characters
 *
 * Detects characters that have special meaning in shell syntax
 * like pipes, redirections, quotes, etc.
 *
 * @param str String to check
 * @param c Character found if special character exists
 * @return 1 if special character found, 0 otherwise
 */
int		special_char(char *str, char *c);

/**
 * @brief Extracts the next command argument
 *
 * Parses the input string to find the next complete argument,
 * handling quotes and escapes properly.
 *
 * @param c Pointer to store the last character processed
 * @param str Input string to parse
 * @return Next argument or NULL if no more arguments
 */
char	*get_next_argument(char *c, char *str);

/**
 * @brief Basic string splitting function
 *
 * Splits a string on a delimiter character. Unlike ft_split2,
 * this version doesn't handle quotes specially.
 *
 * @param arg String to split
 * @param c Delimiter character
 * @return Array of strings, NULL-terminated, or NULL on error
 */
char	**simple_split(char *arg, char c);

#endif
