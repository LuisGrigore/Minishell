#ifndef PARSER_H
# define PARSER_H

# include "../external/gen_list/gen_list.h"

t_gen_list	*parse_tokens_to_commands(t_gen_list *tokens);
t_gen_list *parse_line(char *line);

#endif