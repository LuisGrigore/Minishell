#include "command_internal.h"
#include <stdio.h>

int export_execute(t_command *command, t_gen_list *envioroment)
{
    t_gen_list_iter *it;
    char *arg;
    char **new_variable;

    if (!command || !command->args || gen_list_is_empty(command->args) || !envioroment)
        return (COMMAND_MALFORMED_ERR);
    it = gen_list_iter_start(command->args);
    if (!it)
        return (MS_ALLOCATION_ERR);
    arg = gen_list_iter_next(it);
    arg = gen_list_iter_next(it);
    gen_list_iter_destroy(it);
    if (!arg)
        return;
    new_variable = ft_split2(arg, '=');
    if (!new_variable || !new_variable[0] || !new_variable[1])
        return (COMMAND_MALFORMED_ERR);
    env_set(envioroment, new_variable[0], new_variable[1]);
    free(new_variable[0]);
    free(new_variable[1]);
    free(new_variable);
    return (MS_OK);
}
int unset_execute(t_command *command, t_gen_list *envioroment)
{
    t_gen_list_iter *it;
    char *arg;

    if (!command || !command->args || !envioroment)
        return (COMMAND_MALFORMED_ERR);
    it = gen_list_iter_start(command->args);
    if (!it)
        return (MS_ALLOCATION_ERR);
    arg = gen_list_iter_next(it);
    arg = gen_list_iter_next(it);
    if (arg)
        env_unset(envioroment, arg);
    gen_list_iter_destroy(it);
    return (MS_OK);
}

int echo_execute(t_command *command, t_gen_list *envioroment)
{
    t_gen_list_iter *it;
    char *arg;
    int newline;

    (void)envioroment;
    if (!command || !command->args)
        return (COMMAND_MALFORMED_ERR);
    it = gen_list_iter_start(command->args);
    if (!it)
        return (MS_ALLOCATION_ERR);
    arg = gen_list_iter_next(it);
    arg = gen_list_iter_next(it);
    newline = 1;
    if (arg && ft_strncmp(arg, "-n", 2) == 0 && ft_strlen(arg) == 2)
    {
        newline = 0;
        arg = gen_list_iter_next(it);
    }
    while (arg)
    {
        ft_printf("%s", arg);
        char *next_arg = gen_list_iter_next(it);
        if (next_arg)
            ft_printf(" ");
        arg = next_arg;
    }
    if (newline)
        ft_printf("\n");
    gen_list_iter_destroy(it);
    return (MS_OK);
}
