#ifndef EXECUTER_H
#define EXECUTER_H

#include "../external/gen_list/gen_list.h"
#include "ms_status_codes.h"
#include "mini_state.h"

/**
 * Executes a single command line, similar to how Bash interprets and runs commands.
 *
 * @param line A null-terminated string containing the command line to be parsed and executed.
 *             The command may include:
 *               - simple commands and arguments
 *               - operators for redirection and piping:
 *                   |   (pipe)
 *                   <   (input redirection)
 *                   >   (output redirection, truncate)
 *                   <<  (heredoc)
 *                   >>  (output redirection, append)
 *
 * @param env  A pointer to the environment list (t_gen_list) containing only
 *             internal state variables (e.g., last return code, execution flags).
 *
 * @return An integer representing the exit status of the executed command.
 *         By convention, 0 indicates success, while non-zero values indicate errors,
 *         similar to Bash’s return codes.
 *
 * This function parses and executes the provided command line using the given state
 * environment. Its behavior mimics that of the Bash shell when handling execution,
 * redirections, and pipes, but it relies only on the provided state variables
 * rather than a full environment.
 */
int execute_line(char *line, t_mini_state *mini_state);

#endif