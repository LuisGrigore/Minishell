#include "command_internal.h"
#include <stdio.h>

int export_execute(t_command *command, t_gen_list *environment)
{
    t_gen_list_iter *it;
    char *arg;
    char **new_variable;

    if (!command || !command->args || gen_list_is_empty(command->args)|| !environment)
        return(EXECUTER_ERR);
    it = gen_list_iter_start(command->args);
    if (!it)
        return(GEN_LIST_IS_NULL_ERR);
    arg = gen_list_iter_next(it);
    arg = gen_list_iter_next(it);
    gen_list_iter_destroy(it);
    if (!arg)
        return(EXECUTER_ERR);
    new_variable = ft_split2(arg, '=');
    if (!new_variable || !new_variable[0] || !new_variable[1])
        return(BINBUILTIN_ERROR);
    env_set(environment, new_variable[0], new_variable[1]);
    free(new_variable[0]);
    free(new_variable[1]);
    free(new_variable);
    return(BINBUILTIN_SUCCESS);
}
int unset_execute(t_command *command, t_gen_list *environment)
{
    t_gen_list_iter *it;
    char *arg;

    if (!command || !command->args || !environment)
        return(-1);
    it = gen_list_iter_start(command->args);
    if (!it)
        return(GEN_LIST_IS_NULL_ERR);
    arg = gen_list_iter_next(it);
    arg = gen_list_iter_next(it);
    if (arg)
        env_unset(environment, arg);
    gen_list_iter_destroy(it);
    return(BINBUILTIN_SUCCESS);
}

int echo_execute(t_command *command, t_gen_list *environment)
{
    t_gen_list_iter *it;
    char *arg;
    int newline;

    (void)environment;
    if (!command || !command->args)
        return(-1);
    it = gen_list_iter_start(command->args);
    if (!it)
        return(GEN_LIST_IS_NULL_ERR);
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
    return(BINBUILTIN_SUCCESS);
}
