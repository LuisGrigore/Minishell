#include "../include/command.h"
# include "../include/redirect.h"
# include "../external/gen_list/gen_list.h"
#include "../external/libft/libft.h"
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
		gen_list_destroy(command->args, free);
	if (command->redirects)
		gen_list_destroy(command->redirects, destroy_redirect);
	;
	free(command);
}
