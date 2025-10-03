#include "command_internal.h"

void command_push_arg(t_command *command, char *arg)
{
    gen_list_push_back(command->args, ft_strdup(arg));
}

void command_push_redirect(t_command *command, t_redirect_type redirect_type, char *file_name)
{
    gen_list_push_back(command->redirects, redirect_create(redirect_type, file_name));
}

//TODO :: Hacer que si hay redirects, redirija la entrada y salida del proceso al archivo adecuado
int command_exec(t_command *command, t_gen_list *environment)
{
    command->command_funct(command, environment);
}