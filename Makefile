CC      = gcc
CFLAGS  = -fsanitize=address -g
INCLUDES =  -I./environment -I./external/gen_list -I./external/gen_list/gen_link_list -I./external/libft -I./include -I./parser -I./parser/include -I./parser/lexer

OBJ_DIR = obj
NAME    = minishell

SRCS    = ./executer/find_command.c ./executer/pipe.c ./utils/ft_split2.0.c ./utils/path_utils.c ./parser/lexer/lexer_util.c ./parser/lexer/lexer_life_cycle.c ./parser/lexer/lexer_tokenize.c ./parser/parser.c ./environment/environment_operations.c ./environment/environment_serialization_deserialization.c ./environment/envioroment_internal.c ./environment/environment_query.c ./command/command.c ./command/redirect_asignation.c ./command/redirect.c ./command/command_functs.c ./minishell.c 
OBJS    = $(SRCS:%.c=$(OBJ_DIR)/%.o)
LINK_FLAGS = -lreadline -lncurses
SUBSYSTEM_PATH = ./external/libft ./external/gen_list
SUBSYSTEM_LIB  = ./external/libft/libft.a ./external/gen_list/gen_list.a

all: subsystems $(NAME)

subsystems:
	@for dir in $(SUBSYSTEM_PATH); do \
		$(MAKE) -C $$dir all; \
	done

$(NAME): $(OBJS) $(SUBSYSTEM_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LINK_FLAGS)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	@for dir in $(SUBSYSTEM_PATH); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -rf $(OBJ_DIR)

fclean: clean
	@for dir in $(SUBSYSTEM_PATH); do \
		$(MAKE) -C $$dir fclean; \
	done
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re subsystems
