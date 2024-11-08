NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I includes -I src/libft

SRCS = 	src/parsing/expenser.c src/parsing/expenser_2.c src/parsing/free_parsing.c \
		src/parsing/lexer.c src/parsing/lexer_2.c src/parsing/lexer_3.c src/parsing/lexer_4.c src/parsing/lexer_5.c \
		src/parsing/parser.c src/parsing/parser_2.c src/parsing/parser_3.c \
		src/builtin/cd.c src/builtin/echo.c src/builtin/env.c src/builtin/exit.c src/builtin/export.c src/builtin/pwd.c src/builtin/unset.c \
		src/exec/exec.c src/exec/pipes.c src/exec/redirs.c src/exec/utils.c src/exec/free_utils.c src/main.c

LIBFT_DIR = src/libft
LIBFT_SRCS = $(wildcard $(LIBFT_DIR)/*.c)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

OBJS = $(SRCS:.c=.o) $(LIBFT_OBJS)

RM = rm -f

all: $(LIBFT_DIR)/libft.a $(NAME)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re