#include "command_internal.h"

bool command_is_built_in(t_command *command)
{
	return command->is_builtin;
}