#include"redirect_manager_internal.h"
#include <stdio.h>

t_redirect *redirect_create(t_redirect_type redirect_type, char *file_name)
{
    t_redirect *r = malloc(sizeof(t_redirect));
    if (!r) return NULL;
    r->redirect_simbol = redirect_type;
    if (file_name) {
        r->file = malloc(ft_strlen(file_name) + 1);
        if (!r->file) { free(r); return NULL; }
        ft_strlcpy(r->file, file_name, ft_strlen(file_name) + 1);
    } else {
        r->file = NULL;
    }
    return r;
}

void redirect_destroy(t_redirect *redirect)
{
	free(redirect->file);
	free(redirect);
}

int redirect_execute(t_redirect *redirect)
{
	(void *) redirect;
    perror("redirect_execute: not implemented");
    exit(EXIT_FAILURE);
    return -1; // never reached, but silences compiler warning
}