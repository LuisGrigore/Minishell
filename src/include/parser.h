#ifndef PARSER_H
# define PARSER_H

# include "../external/gen_list/gen_list.h"

/**
 * Parses a raw command line string into a structured list of commands.
 *
 * This function is the high-level entry point for transforming user input
 * into executable command objects. It performs the following steps:
 *
 *   1. Tokenizes the input string using.
 *   2. Converts the list of tokens into command objects.
 *   3. Cleans up the intermediate token list.
 *
 * @param line A null-terminated string containing the user input.
 *
 * @return A list (t_gen_list) of t_command* objects representing the parsed
 *         commands, or NULL if parsing fails at any stage.
 *
 * Example:
 *   Input:  "ls -l | grep txt > out.txt"
 *   Output: A list of two t_command structures:
 *              - Command 1: "ls" with argument "-l"
 *              - Command 2: "grep" with argument "txt" and output redirection to "out.txt"
 *
 * The caller is responsible for destroying the returned command list
 * using the appropriate cleanup function.
 */
t_gen_list *parse_line(char *line);

#endif