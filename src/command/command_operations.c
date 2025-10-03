#include "command_internal.h"

void command_push_arg(t_command *command, char *arg)
{
    gen_list_push_back(command->args, ft_strdup(arg));
}

void command_push_redirect(t_command *command, t_redirect_type redirect_type, char *file_name)
{
    gen_list_push_back(command->redirects, redirect_create(redirect_type, file_name));
}

//TODO :: Hacer que laas funciones de commando devuelvan un int para manejo de errores.
int command_exec(t_command *command, t_gen_list *environment)
{
    command->command_funct(command, environment);
}