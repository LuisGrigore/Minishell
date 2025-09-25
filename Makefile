
NAME = Minishell

CC = cc 
CFLAGS = -I include/ -Wall -Werror -Wextra -g
RDFLAGS = -lreadline -lncurses 

LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a
SRC = 	init/pipe.c init/minishell.c utils/ft_split2.0.c utils/path_utils.c  init/command.c init/envioroment.c  init/redirect_asignation.c init/find_command.c init/command_functs.c init/list.c 
OBJECTS = $(SRC:.c=.o)

all: subsystems $(NAME)

subsystems:
	@make -C $(LIBFT_PATH) all

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_LIB) -o $(NAME) $(RDFLAGS)

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJECTS)

fclean: clean 
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all
.PHONY: re clean fclean all