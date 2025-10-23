#include "command_internal.h"
#include <stdio.h>

void export_execute(t_command *command, t_gen_list *envioroment)
{
    t_gen_list_iter *it;
    char *arg;
	char **new_variable;

    if (!command || !command->args || gen_list_is_empty(command->args)|| !envioroment)
        return;
    it = gen_list_iter_start(command->args);
    if (!it)
        return;
    arg = gen_list_iter_next(it);
    arg = gen_list_iter_next(it);
    gen_list_iter_destroy(it);
    if (!arg)
        return;
    new_variable = ft_split2(arg, '=');
    printf("%s\n,%s\n",new_variable[0],new_variable[1]);
    if (!new_variable || !new_variable[0] || !new_variable[1])
        return;
    env_set(envioroment, new_variable[0], new_variable[1]);
    for (size_t i = 0; i < 2; i++)
        free(new_variable[i]);
    free(new_variable);
}
void unset_execute(t_command *command, t_gen_list *envioroment)
{
    t_gen_list_iter *it;
    char *arg;

    if (!command || !command->args || !envioroment)
        return;
    it = gen_list_iter_start(command->args);
    if (!it)
        return;
    arg = gen_list_iter_next(it);
    arg = gen_list_iter_next(it);
    if (arg)
        env_unset(envioroment, arg);

    gen_list_iter_destroy(it);
}

void echo_execute(t_command *command, t_gen_list *envioroment)
{
    t_gen_list_iter *it;
    char *arg;
    int newline = 1;

    (void)envioroment;
    if (!command || !command->args)
        return;
    it = gen_list_iter_start(command->args);
    if (!it)
        return;
    arg = gen_list_iter_next(it);
    arg = gen_list_iter_next(it);
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
    //exit(0);
}