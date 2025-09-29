NAME	= list.a
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g 

SRCS	= list.c

OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re clean fclean all bonus
