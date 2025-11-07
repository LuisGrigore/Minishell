#include "command_internal.h"
#include "unistd.h"

static int	handle_list_errors(t_gen_list_status_code list_status_code)
{
	switch (list_status_code)
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

int	command_push_arg(t_command *command, char *arg)
{
	return (handle_list_errors(gen_list_push_back(command->args,
				ft_strdup(arg))));
}

int	command_push_redirect(t_command *command, t_redirect_type redirect_type,
		char *file_name)
{
	return (handle_list_errors(gen_list_push_back(command->redirects,
				redirect_create(redirect_type, file_name))));
}

static int command_redirects_execute(t_command *command, t_mini_state *mini_state)
{
	t_gen_list_iter *it;
	t_redirect *current_redirect;
	int status_code;

	if (!command->redirects)
		return (COMMAND_MALFORMED_ERR);
	it = gen_list_iter_start(command->redirects);
	if (!it)
		return (MS_ALLOCATION_ERR);
	status_code = MS_OK;
	while (1)
	{
		current_redirect = (t_redirect *) gen_list_iter_next(it);
		if(!current_redirect || status_code != MS_OK)
			break ;
		status_code = redirect_execute(current_redirect, mini_state);
	}
	gen_list_iter_destroy(it);
	return (status_code);
}

int	command_exec(t_command *command, t_mini_state *mini_state)
{
	int	status_code;
	int	stdin_backup;
	int	stdout_backup;

	mini_state_set_last_command(mini_state,
		(char *)gen_list_peek_top(command->args));
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup == -1 || stdout_backup == -1)
		return (MS_ALLOCATION_ERR);
	status_code = command_redirects_execute(command, mini_state);
	if (status_code != MS_OK)
	{
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
		return (status_code);
	}
	status_code = command->command_funct(command, mini_state_get_environment_vars(mini_state));
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	return (status_code);
}
