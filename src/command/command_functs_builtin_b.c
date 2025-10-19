#include "command_internal.h"

int cd_execute(t_command *command, t_gen_list *environment)
{
    t_gen_list_iter *it;
    char *old_directory;
    char *target;

    if (!command || !command->args || gen_list_get_size(command->args) < 2)
    {
        fprintf(stderr, "cd: missing argument\n");
        return (COMMAND_MALFORMED_ERR);
    }
    old_directory = env_get(environment, "PWD");
    it = gen_list_iter_start(command->args);
    gen_list_iter_next(it);
    target = gen_list_iter_next(it);
    if (access(target, F_OK) == 0)
    {
        if (chdir(target) == -1)
        {
            perror("cd");
            free(old_directory);
            return (MS_FILE_ERR);
        }
        if (old_directory)
            env_set(environment, old_directory, "OLDPWD");
        env_set(environment, ft_strdup(target), "PWD");
        free(old_directory);
        return (MS_OK);
    }
    if (old_directory)
    {
        char *joined_path = ft_strjoin(old_directory, target);
        if (access(joined_path, F_OK) == 0)
        {
            if (chdir(joined_path) == -1)
            {
                perror("cd");
                free(joined_path);
                free(old_directory);
                return (MS_FILE_ERR);
            }
            env_set(environment, old_directory, "OLDPWD");
            env_set(environment, joined_path, "PWD");
            free(joined_path);
            free(old_directory);
            return (MS_OK);
        }
        free(joined_path);
    }
    fprintf(stderr, "cd: no such file or directory: %s\n", target);
    free(old_directory);
    return (MS_FILE_ERR);
}

int	pwd_execute(t_command *command, t_gen_list *envioroment)
{
    char *current_dir;
    if (!command)
        return (COMMAND_MALFORMED_ERR);
    current_dir = env_get(envioroment, "PWD");
    if (!current_dir)
        return (MS_FILE_ERR);
    printf("%s\n", current_dir);
    free(current_dir);
    return (MS_OK);
}
int	env_execute(t_command *command, t_gen_list *envioroment)
{
    char **serialized_env;
    int i;
    if (!command)
        return (COMMAND_MALFORMED_ERR);
    serialized_env = env_serialize(envioroment);
    i = 0;
    while (i < (int)gen_list_get_size(envioroment))
    {
        printf("%s\n", serialized_env[i]);
        i++;
    }
    free_double_pointer(serialized_env);
    return (MS_OK);
}