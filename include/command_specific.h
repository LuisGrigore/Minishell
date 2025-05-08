#ifndef COMMAND_SPECIFIC_H
# define COMMAND_SPECIFIC_H

typedef struct s_bin_cmd
{
    char **cmd;
    char *path;

}   t_bin_cmd;
typedef struct s_builtin_cmd
{
    char *chs;
    char **cmd;
} t_builtin_cmd ;

t_bin_cmd *init_bin_cmd(char **cmd, char *path);
t_builtin_cmd *init_builtin_cmd(char **cmd, char *chs);
#endif