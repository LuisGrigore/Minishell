#include "command_internal.h"
#include "unistd.h"


void command_push_arg(t_command *command, char *arg)
{
    gen_list_push_back(command->args, ft_strdup(arg));
}

void command_push_redirect(t_command *command, t_redirect_type redirect_type, char *file_name)
{
    gen_list_push_back(command->redirects, redirect_create(redirect_type, file_name));
}

static void redirect_execute_data(void *redirect_ptr)
{

	t_redirect *redirect = (t_redirect *) redirect_ptr;
	redirect_execute(redirect);
}

//TODO :: Hacer que laas funciones de commando devuelvan un int para manejo de errores.
int command_exec(t_command *command, t_gen_list *environment)
{
    int stdin_backup = dup(STDIN_FILENO);
    int stdout_backup = dup(STDOUT_FILENO);

    gen_list_for_each(command->redirects, redirect_execute_data);
    command->command_funct(command, environment);

    // Restauramos stdin y stdout ANTES de borrar
    dup2(stdin_backup, STDIN_FILENO);
    dup2(stdout_backup, STDOUT_FILENO);

    close(stdin_backup);
    close(stdout_backup);

    return 0;
}