#include "../include/redirect_asignation.h"
#include "../include/util.h"
#include "../libft/libft.h"

static t_redirect_type	get_redirection_type_from_str(char *str);
static char				*first_redirection(char *str);
static char				*get_file_from_str(char *str, char *redirection);

t_gen_list	*get_redirects_from_str_arr(char *str)
{
	t_gen_list	*redirects;
	t_redirect	*current_node_value;
	char		*current_redirecction;
	int			i;

	redirects = init_list();
	current_redirecction = first_redirection(str);
	while (current_redirecction != NULL)
	{
		current_node_value = init_redirect(get_file_from_str(str,
					current_redirecction),
				get_redirection_type_from_str(current_redirecction));
		push_end(redirects, current_node_value);
		i = special_char(str, current_redirecction)
			+ (int)ft_strlen(current_redirecction);
		str = str + i;
		current_redirecction = first_redirection(str);
	}
	if (redirects->head == NULL)
	{
		free(redirects);
		redirects = NULL;
	}
	return (redirects);
}
static char	*first_redirection(char *str)
{
	int	l;
	int	r;
	int	dl;
	int	dr;

	l = special_char(str, "<");
	r = special_char(str, ">");
	dl = special_char(str, "<<");
	dr = special_char(str, ">>");
	if (l < r && l < dl && l < dr)
		return ("<");
	if (r < l && r < dl && r < dr)
		return (">");
	if (dl < r && dl < l && dl < dr)
		return ("<<");
	if (dr < l && dr < dl && dr < r)
		return (">>");
	return (NULL);
}

static char	*get_file_from_str(char *str, char *redirection)
{
	int	end;
	int	start;

	start = special_char(str, redirection);
	start++;
	while (str[start] && ft_ispace(str[start]) == 1)
		start++;
	end = start;
	while (str[end] && ft_ispace(str[end] == 0))
		end++;
	return (ft_substr(str, start, (size_t)end));
}
static t_redirect_type	get_redirection_type_from_str(char *str)
{
	if (ft_strncmp(str, "<", 1) == 0)
		return (LEFT_REDIRECT);
	if (ft_strncmp(str, ">", 1) == 0)
		return (RIGHT_REDIRECT);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (DOUBLE_RIGHT_REDIRECT);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (DOUBLE_LEFT_REDIRECT);
	return (ERROR);
}
t_redirect *init_redirect(char *file, t_redirect_type redirect_type) {
    t_redirect *r = malloc(sizeof(t_redirect));
    if (!r) return NULL;
    r->redirect_simbol = redirect_type;
    if (file) {
        r->file = malloc(ft_strlen(file) + 1);
        if (!r->file) { free(r); return NULL; }
        ft_strlcpy(r->file, file, ft_strlen(file) + 1);
    } else {
        r->file = NULL;
    }
    return r;
}
void	destroy_redirect(void *redirect)
{
	t_redirect	*aux;

	aux = (t_redirect *)redirect;
	free(aux->file);
	free(aux);
}
