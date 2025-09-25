CC      = cc
CFLAGS  = -Wall -Wextra -Werror
INCLUDES =  -I./include -I./libft

OBJ_DIR = obj
NAME    = minishel

SRCS    = ./src/init/command.c ./src/init/envioroment.c ./src/init/redirect_asignation.c ./src/init/find_command.c ./src/init/redirect.c ./src/init/pipe.c ./src/init/list.c ./src/init/minishell.c ./src/init/command_functs.c ./src/utils/ft_split2.0.c ./src/utils/path_utils.c 
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
