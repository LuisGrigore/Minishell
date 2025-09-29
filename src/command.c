#include "../include/command.h"
# include "../include/redirect_asignation.h"
#include "../list/list.h"
#include "../libft/libft.h"
#include "stdlib.h"
#include <stdio.h>


t_command	*init_command(t_gen_list *args, t_command_funct funct,
		t_gen_list *redirects)
{
	t_command	*new_command;

	new_command = ft_calloc(1, sizeof(t_command));
	new_command->args = args;
	new_command->command_funct = funct;
	new_command->redirects = redirects;
	return (new_command);
}

void	destroy_command(void *command_to_delete)
{
	t_command	*command;

	command = (t_command *)command_to_delete;
	if (command->args)
		destroy_gen_list(command->args, free);
	if (command->redirects)
		destroy_gen_list(command->redirects, destroy_redirect);
	;
	free(command);
}
