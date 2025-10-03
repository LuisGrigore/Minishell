#ifndef EXECUTER_H
#define EXECUTER_H

#include "../external/gen_list/gen_list.h"

//COMMAND EXECUTIONER
/**
 * @brief Executes the commands in the given list in order as child processes linking their input and output with the corresponding pipes.
 *
 * @param commands Command list to execute
 * @param env Environment variable list that the commands may need.
 */
void execute_commands_with_pipes(t_gen_list *commands, t_gen_list *env);

#endif