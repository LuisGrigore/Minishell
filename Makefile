CC      = cc
CFLAGS  = -Wall -Wextra -Werror
INCLUDES =  -I./include -I./libft

OBJ_DIR = obj
NAME    = minishell

SRCS    = ./src/init/command.c ./src/init/envioroment.c ./src/init/redirect_asignation.c ./src/init/find_command.c ./src/init/redirect.c ./src/init/pipe.c ./src/init/list.c ./src/init/minishell.c ./src/init/command_functs.c ./src/utils/ft_split2.0.c ./src/utils/path_utils.c ./libft/ft_bzero.c ./libft/ft_putnbr_fd.c ./libft/get_next_line.c ./libft/ft_isascii.c ./libft/ft_itoa.c ./libft/ft_memset.c ./libft/ft_strlcpy.c ./libft/ft_strrchr.c ./libft/ft_lstsize_bonus.c ./libft/ft_lstnew_bonus.c ./libft/ft_strncmp.c ./libft/ft_memcpy.c ./libft/ft_putpointer.c ./libft/ft_memchr.c ./libft/ft_lstadd_back_bonus.c ./libft/ft_puthexnumax.c ./libft/ft_strlen.c ./libft/ft_printf.c ./libft/ft_putendl_fd.c ./libft/ft_strmapi.c ./libft/ft_striteri.c ./libft/ft_atol.c ./libft/ft_lstlast_bonus.c ./libft/ft_lstadd_front_bonus.c ./libft/ft_strlcat.c ./libft/ft_calloc.c ./libft/ft_strtrim.c ./libft/ft_putstr.c ./libft/ft_dbpt_free.c ./libft/ft_toupper.c ./libft/ft_strchr.c ./libft/ft_isdigit.c ./libft/ft_split.c ./libft/ft_atoi.c ./libft/ft_putunmath.c ./libft/ft_tolower.c ./libft/ft_puthexnum.c ./libft/ft_strdup.c ./libft/get_next_line_utils.c ./libft/ft_putnb.c ./libft/ft_putchar.c ./libft/ft_putchar_fd.c ./libft/ft_selector.c ./libft/ft_memcmp.c ./libft/ft_putstr_fd.c ./libft/ft_strjoin.c ./libft/ft_strnstr.c ./libft/ft_isalpha.c ./libft/ft_isalnum.c ./libft/ft_memmove.c ./libft/ft_substr.c ./libft/ft_isprint.c 
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
