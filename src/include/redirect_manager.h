#ifndef REDIRECT_ASIGNATION_H
# define REDIRECT_ASIGNATION_H
//TODO :: Quitar cuando sea posible.
# include "../external/gen_list/gen_list.h"

typedef enum e_redirect_type
{
	LEFT_REDIRECT,
	RIGHT_REDIRECT,
	DOUBLE_LEFT_REDIRECT,
	DOUBLE_RIGHT_REDIRECT,
	NONE,
	ERROR,
}					t_redirect_type;

typedef struct s_redirect t_redirect;

//TODO :: Quitar esto cuando se pueda.
t_gen_list			*get_redirects_from_str_arr(char *str);

/**
 * @brief Creates a new redirect structure.
 * 
 * @param redirect_type The type of the redirect (input, output, append).
 * @param file_name The target file for the redirection.
 * @return A pointer to the newly created redirect structure.
 */
t_redirect *redirect_create(t_redirect_type redirect_type, char *file_name);

/**
 * @brief Destroys a redirect structure and frees memory.
 * 
 * @param redirect Pointer to the redirect structure to destroy.
 */
void redirect_destroy(t_redirect *redirect);

/**
 * @brief Executes a redirect.
 * 
 * This function applies the redirection to the current process.
 * 
 * @param redirect Pointer to the redirect structure.
 * @return 0 on success, -1 on error.
 */
int redirect_execute(t_redirect *redirect);

//DEBUG
void print_redirect(void *redir_ptr);

#endif