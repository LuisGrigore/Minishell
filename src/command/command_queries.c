#include "command_internal.h"

bool command_is_built_in(t_command *command)
{
	if (!command)
		return false;
	return command->is_builtin;
}

char *command_get_name(t_command *command)
{
	if (!command)
		return NULL;
	return ((char *)gen_list_peek_top(command->args));
}