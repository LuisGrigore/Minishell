NAME	= gen_list.a
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g -I. -Igen_link_list

SRCS	= \
	gen_link_list/iteration/gen_link_list_iteration_life_cycle.c \
	gen_link_list/iteration/gen_link_list_iteration.c \
	gen_link_list/life_cycle/gen_link_list_life_cycle.c \
	gen_link_list/serialization/gen_link_list_serialization.c \
	gen_link_list/operations/gen_link_list_deletion.c \
	gen_link_list/operations/gen_link_list_insertion.c \
	gen_link_list/operations/gen_link_list_retrieval.c \
	gen_link_list/queries/gen_link_list_find.c \
	gen_link_list/queries/gen_link_list_peek.c \
	gen_link_list/queries/gen_link_list_get_size.c \
	gen_link_list/queries/gen_link_list_predicates.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
