NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/parsing/lexer.c src/parsing/expenseur.c src/parsing/parser.c src/parsing/testeur_parsing.c


OBJS = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re