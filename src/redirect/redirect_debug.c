#include "redirect_internal.h"
#include <stdio.h>

void print_redirect(void *redir_ptr)
{
	t_redirect *redir = (t_redirect *) redir_ptr;
    if (!redir) return;
    const char *type_str;
    switch (redir->redirect_simbol) {
        case LEFT_REDIRECT: type_str = "<"; break;
        case RIGHT_REDIRECT: type_str = ">"; break;
        case DOUBLE_LEFT_REDIRECT: type_str = "<<"; break;
        case DOUBLE_RIGHT_REDIRECT: type_str = ">>"; break;
        case NONE: type_str = "NONE"; break;
        case ERROR: type_str = "ERROR"; break;
        default: type_str = "UNKNOWN"; break;
    }
    printf("    Redirect: %s %s\n", type_str, redir->file);
}