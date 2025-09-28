CC      = cc
CFLAGS  = 
INCLUDES =  -I./include -I./libft

OBJ_DIR = obj
NAME    = minishell

SRCS    = ./src/command.c ./src/envioroment.c ./src/ft_split2.0.c ./src/redirect_asignation.c ./src/tokenizer.c ./src/find_command.c ./src/redirect.c ./src/pipe.c ./src/path_utils.c ./src/list.c ./src/minishell.c ./src/command_functs.c ./src/parser.c 
OBJS    = $(SRCS:%.c=$(OBJ_DIR)/%.o)
LINK_FLAGS = -lreadline -lncurses
SUBSYSTEM_PATH = ./libft
SUBSYSTEM_LIB  = ./libft/libft.a

all: subsystems $(NAME)

subsystems:
	$(MAKE) -C $(SUBSYSTEM_PATH) all

$(NAME): $(OBJS) $(SUBSYSTEM_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LINK_FLAGS)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(MAKE) -C $(SUBSYSTEM_PATH) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(SUBSYSTEM_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re subsystems
