CC      = cc
CFLAGS  = -Wall -Wextra -Werror
INCLUDES =  -I. -I./command -I./environment -I./executer -I./external/gen_list -I./external/gen_list/gen_link_list -I./external/libft -I./handle_status_code -I./history_manager -I./include -I./lexer -I./mini_state -I./parser -I./pipe_manager -I./redirect_manager -I./signal_manager

OBJ_DIR = obj
NAME    = minishell

SRCS    = ./history_manager/history_manager.c ./executer/executer_with_pipes.c ./executer/executer.c ./utils/path_utils.c ./handle_status_code/handle_status_code_a.c ./handle_status_code/handle_status_code_c.c ./handle_status_code/handle_status_code_b.c ./parser/parser_handle_tokens.c ./parser/parser_utils.c ./parser/parser.c ./mini_state/mini_state_operations_b.c ./mini_state/mini_state_operations_a.c ./mini_state/mini_state_lifecycle.c ./signal_manager/signal_manager_utils.c ./signal_manager/signal_manager.c ./redirect_manager/redirect_heredoc_manger.c ./redirect_manager/redirect_manager.c ./environment/environment_serialization_deserialization.c ./environment/environment_operations_a.c ./environment/envioroment_internal.c ./environment/envioroment_operations_b.c ./environment/environment_query.c ./lexer/lexer_util_b.c ./lexer/lexer_util_a.c ./lexer/lexer.c ./lexer/lexer_life_cycle.c ./lexer/lexer_build_word.c ./lexer/lexer_add_token.c ./lexer/lexer_token.c ./command/command_functs_bin_b.c ./command/command_functs_builtin_b.c ./command/command_queries.c ./command/command_operations_a.c ./command/command_functs_builtin_a.c ./command/command_lifecycle.c ./command/command_functs_builtin_c.c ./command/command_operations_b.c ./command/command_functs_bin_a.c ./pipe_manager/pipe_manager.c ./pipe_manager/pipe_manager_operations.c ./minishell.c 
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
