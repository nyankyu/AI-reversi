NAME = ai-reversi
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = \
	main.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)
	./$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
