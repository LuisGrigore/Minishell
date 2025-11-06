#include "environment_internal.h"


static char *get_var_name(char *line, size_t start, size_t *len)
{
    size_t j;
    char *name;

    j = 0;
    while (line[start + j] && (ft_isalnum(line[start + j]) || line[start + j] == '_' ||line[start + j] == '?'))
        j++;
    *len = j;
    if (j == 0)
        return NULL;
    name = ft_substr(line, start, j);
    return name;
}

static char *append_value_with_quotes(char *result, char *value)
{
    char *tmp;
    char *new_result;

 

    tmp = result;
    new_result = ft_strjoin(result, value);
    free(tmp);
    return (new_result);
}

static char *append_char(char *result, char c)
{
    char *tmp;
    char *s;
    char *new_result;

    s = malloc(2);
    s[0] = c;
    s[1] = '\0';
    tmp = result;
    new_result = ft_strjoin(result, s);
    free(tmp);
    free(s);
    return new_result;
}

char *env_expand_vars(t_gen_list *env, char *line)
{
    char *result;
    char *var_name;
    char *value;
    size_t i;
    size_t len;

    if (!line)
        return NULL;
    result = ft_strdup("");
    i = 0;
    while (line[i])
    {
        if (line[i] == '$')
        {
            var_name = get_var_name(line, i + 1, &len);
            if (var_name)
            {
                value = env_get(env, var_name);
                free(var_name);
                if (value)
                {
                    result = append_value_with_quotes(result, value);
                    free(value);
                }
            }
            i += len + 1;
        }
        else
        {
            result = append_char(result, line[i]);
            i++;
        }
    }
    return result;
}
