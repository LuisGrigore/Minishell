#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <stdbool.h>

/**
 * Adds a command line to the shell history, with minimal validation.
 *
 * The function first checks the given line:
 *   - Filters out empty or whitespace-only commands.
 *   - Avoids adding lines starting/ending with `|`.
 *   - Ensures that unclosed quotes are not stored.
 *
 * If the command passes these checks, it is appended to the history
 * using `add_history()`. Otherwise, nothing is added.
 *
 * @param line A null-terminated string containing the command to be stored.
 *
 * @return true if the command was successfully added to the history,
 *         false if it was rejected.
 */
bool history_add(char *line);

#endif