#include "../include/command_specific.h"
#include "../libft/libft.h"

t_builtin_cmd *init_builtin_cmd(char **cmd, char *chs)
{
    t_builtin_cmd *builtin;
    builtin = ft_caalloc(1, sizeof(t_builtin_cmd));
    builtin->cmd = cmd;
    builtin->chs = chs;
    return builtin;
}


t_bin_cmd *init_bin_cmd(char **cmd, char *path)
{
    t_bin_cmd *bin;
    bin = ft_caalloc(1, sizeof(t_bin_cmd));
    bin->cmd = cmd;
    bin->path = path;
    return bin;
}