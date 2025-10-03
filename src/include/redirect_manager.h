#ifndef REDIRECT_ASIGNATION_H
# define REDIRECT_ASIGNATION_H
# include "../external/gen_list/gen_list.h"


/* ============================================================
**  Data Structures
** ============================================================
*/
/**
 * @enum e_redirect_type
 * @brief Enumeration of possible redirection types.
 *
 * LEFT_REDIRECT          : Input redirection ("<").
 * RIGHT_REDIRECT         : Output redirection (">"), truncates the file.
 * DOUBLE_LEFT_REDIRECT   : Heredoc ("<<"), reads input until a delimiter.
 * DOUBLE_RIGHT_REDIRECT  : Output append redirection (">>").
 * NONE                   : No redirection.
 * ERROR                  : Invalid or unrecognized redirection.
 */
typedef enum e_redirect_type
{
    LEFT_REDIRECT,
    RIGHT_REDIRECT,
    DOUBLE_LEFT_REDIRECT,
    DOUBLE_RIGHT_REDIRECT,
    NONE,
    ERROR,
} t_redirect_type;

/**
 * @struct s_redirect
 * @brief Opaque structure representing a redirection.
 *
 * Contains the redirection type and the target file or heredoc delimiter.
 */
typedef struct s_redirect t_redirect;

/* ============================================================
**  Lifecycle
** ============================================================
*/

/**
 * @brief Creates a new redirect structure.
 * 
 * Allocates and initializes a redirect object with the given type and target file.
 * The file name is typically duplicated internally to ensure memory safety.
 * 
 * @param redirect_type The type of the redirection (see t_redirect_type).
 * @param file_name The target file name or heredoc delimiter.
 * @return A pointer to the newly created redirect structure, or NULL on failure.
 */
t_redirect *redirect_create(t_redirect_type redirect_type, char *file_name);

/**
 * @brief Destroys a redirect structure and frees its memory.
 * 
 * Safely releases both the redirect object and its associated file name.
 * 
 * @param redirect Pointer to the redirect structure to destroy.
 */
void redirect_destroy(t_redirect *redirect);

/* ============================================================
**  Operations
** ============================================================
*/

/**
 * @brief Executes a redirect in the current process context.
 * 
 * Applies the redirection according to its type:
 *   - Input redirection opens the file for reading and replaces STDIN.
 *   - Output redirection opens the file for writing (truncate/append) and replaces STDOUT.
 *   - Heredoc creates a temporary input from the given delimiter.
 * 
 * @param redirect Pointer to the redirect structure.
 * @return 0 on success, -1 on error (e.g., file not found, permission denied).
 */
int redirect_execute(t_redirect *redirect);

/* ============================================================
**  Debug
** ============================================================
*/

/**
 * @brief Prints a redirect for debugging purposes.
 * 
 * Displays the type of redirection and the associated file name.
 * Used mainly for development and testing.
 * 
 * @param redir_ptr Generic pointer to a t_redirect structure.
 */
void print_redirect(void *redir_ptr);

#endif