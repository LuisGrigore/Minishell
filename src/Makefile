CC      = cc
CFLAGS  = 
INCLUDES =  -I./command -I./environment -I./executer -I./external/gen_list -I./external/gen_list/gen_link_list -I./external/libft -I./include -I./lexer -I./parser -I./pipe_manager -I./redirect_manager -I./signal_manager

OBJ_DIR = obj
NAME    = minishell

SRCS    = ./executer/executer.c ./utils/ft_split2.0.c ./utils/path_utils.c ./parser/parser.c ./signal_manager/signal_manager_utils.c ./signal_manager/signal_manager.c ./redirect_manager/redirect_manager_utils.c ./redirect_manager/redirect_manager_debug.c ./redirect_manager/redirect_manager.c ./environment/environment_operations.c ./environment/environment_serialization_deserialization.c ./environment/envioroment_internal.c ./environment/environment_query.c ./lexer/lexer_debug.c ./lexer/lexer_util.c ./lexer/lexer_life_cycle.c ./lexer/lexer_tokenize.c ./command/command_functs_builtin_b.c ./command/command_operations.c ./command/command_functs_builtin_a.c ./command/command_functs_bin.c ./command/command_lifecycle.c ./command/command_debug.c ./pipe_manager/pipe_manager.c ./minishell.c 
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
