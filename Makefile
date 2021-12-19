NAME = ai-reversi
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
SRC = \
	main.c \
	board.c \
	com.c \
	rule.c \
	tree.c \
	node.c
OBJS = $(SRC:.c=.o)

.PHONY: all clean fclean re run tags debug

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

tags:
	ctags -R --languages=C .

debug: fclean
	gcc -Wall -Werror -Wextra -g -fsanitize=address -DLEAKS=1 -o $(NAME) $(SRC)
