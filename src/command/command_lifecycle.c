#include "command_internal.h"

static t_command_funct get_command_function(char *cmd_name)
{
    if (!cmd_name || ft_strlen(cmd_name) == 0)
        return NULL;

    if (ft_strncmp(cmd_name, "echo", 5) == 0)
        return echo_execute;
    else if (ft_strncmp(cmd_name, "cd", 3) == 0)
        return cd_execute;
    else if (ft_strncmp(cmd_name, "pwd", 4) == 0)
        return pwd_execute;
    else if (ft_strncmp(cmd_name, "export", 7) == 0)
        return export_execute;
    else if (ft_strncmp(cmd_name, "unset", 6) == 0)
        return unset_execute;
    else if (ft_strncmp(cmd_name, "env", 4) == 0)
        return env_execute;
    else
        return bin_execute;
}

t_command *command_create(char *name)
{
	t_command	*new_command;

	new_command = ft_calloc(1, sizeof(t_command));
	new_command->args = gen_list_create();
	new_command->redirects = gen_list_create();
		new_command->command_funct = get_command_function(name);
	return (new_command);
}

static void redirect_destroy_data(void *redirect_ptr)
{
	redirect_destroy((t_redirect *) redirect_ptr);
}
void command_destroy(t_command *command)
{
	if (command->args)
		gen_list_destroy(command->args, free);
	if (command->redirects)
		gen_list_destroy(command->redirects, redirect_destroy_data);
	;
	free(command);
}
