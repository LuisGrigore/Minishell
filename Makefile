CC      = cc
CFLAGS  = 
INCLUDES =  -I./include -I./libft -I./list -I./src/environment

OBJ_DIR = obj
NAME    = minishell

SRCS    = ./src/command.c ./src/ft_split2.0.c ./src/redirect_asignation.c ./src/tokenizer.c ./src/find_command.c ./src/redirect.c ./src/pipe.c ./src/path_utils.c ./src/environment/environment_operations.c ./src/environment/environment_serialization_deserialization.c ./src/environment/envioroment_internal.c ./src/environment/environment_query.c ./src/minishell.c ./src/command_functs.c ./src/parser.c 
OBJS    = $(SRCS:%.c=$(OBJ_DIR)/%.o)
LINK_FLAGS = -lreadline -lncurses
SUBSYSTEM_PATH = ./libft ./list
SUBSYSTEM_LIB  = ./libft/libft.a ./list/list.a

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
