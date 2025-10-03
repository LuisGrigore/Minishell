#include "command_internal.h"
#include <stdio.h>

void print_command(t_command *cmd, int index)
{
    if (!cmd) return;

    printf("Command #%d:\n", index);

    //Imprimir args
    if (cmd->args && !gen_list_is_empty(cmd->args)) {
        printf("  Args:\n");
        
		t_gen_list_iter *arg_it = gen_list_iter_start(cmd->args);
        char *arg;
        while ((arg = (char *)gen_list_iter_next(arg_it)) != NULL) {
            printf("    %s\n", arg);
        }
    } else {
        printf("  Args: (none)\n");
    }

    //Imprimir redirects
    if (cmd->redirects && !gen_list_is_empty(cmd->redirects)) {
        printf("  Redirects:\n");
        gen_list_for_each(cmd->redirects,print_redirect);
    } else {
        printf("  Redirects: (none)\n");
    }

    printf("\n");
}