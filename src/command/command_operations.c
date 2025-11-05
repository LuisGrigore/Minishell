#include "command_internal.h"
#include "unistd.h"

static int handle_list_errors(t_gen_list_status_code list_status_code)
{
	switch(list_status_code)
	{
		case GEN_LIST_OK:
			return (MS_OK);
		case GEN_LIST_MALLOC_ERR:
			return (MS_ALLOCATION_ERR);
		case GEN_LIST_IS_NULL_ERR:
			return (COMMAND_MALFORMED_ERR);
		default:
			return (COMMAND_ERROR);
	}
}

int command_push_arg(t_command *command, char *arg)
{
	return (handle_list_errors(gen_list_push_back(command->args, ft_strdup(arg))));
}

int command_push_redirect(t_command *command, t_redirect_type redirect_type, char *file_name)
{
    return handle_list_errors(gen_list_push_back(command->redirects, redirect_create(redirect_type, file_name)));
}
//TODO :: Ajustar esto para que funcione con los errores que devuelve redirect_execute, hay que hacer que redirect_execute_data devuelva errores tambien y crear un gen_list_for_each que pueda iterar con una funcion que devuelve error
static int redirect_execute_data(void *redirect_ptr)
{

	t_redirect *redirect = (t_redirect *) redirect_ptr;
	return(redirect_execute(redirect));
}

//TODO :: Hacer que laas funciones de commando devuelvan un int para manejo de errores.
int	command_exec(t_command *command, t_gen_list *environment)
{
	int	status_code;
	int						stdin_backup;
	int						stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup == -1 || stdout_backup == -1)
		return (MS_ALLOCATION_ERR);
	status_code = redirect_error_control(command->redirects, redirect_execute_data);
	if (status_code != MS_OK)
	{
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
		return (status_code);
	}
	status_code = command->command_funct(command, environment);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	if (status_code != MS_OK)
		return (status_code);
	return (MS_OK);
}
