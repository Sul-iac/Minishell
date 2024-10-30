NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	src/parsing/expenser.c src/parsing/expenser_2.c src/parsing/free_parsing.c \
		src/parsing/lexer.c src/parsing/lexer_2.c src/parsing/lexer_3.c src/parsing/lexer_4.c src/parsing/lexer_5.c \
		src/parsing/parser.c src/parsing/parser_2.c src/parsing/parser_3.c \
		


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