NAME = ai-reversi
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
SRC = \
	main.c \
	board.c \
	com.c
OBJS = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)
	./$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
