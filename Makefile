NAME = minishell
CC = gcc
CFLAGS = -g -I includes -lreadline 
SRC_DIR = src/

BUILTINS_DIR = $(SRC_DIR)builtin/cd.c \
				$(SRC_DIR)builtin/echo.c \
				$(SRC_DIR)builtin/env.c \
				$(SRC_DIR)builtin/exit.c \
				$(SRC_DIR)builtin/export.c \
				$(SRC_DIR)builtin/pwd.c \
				$(SRC_DIR)builtin/pwd.c \
				$(SRC_DIR)builtin/unset.c

EXEC_DIR = $(SRC_DIR)exec/exec.c \
			$(SRC_DIR)exec/pipes.c \
			$(SRC_DIR)exec/utils.c

LIB_DIR = $(SRC_DIR)libft


SRCS = $(BUILTINS_DIR) $(EXEC_DIR)

INCLUDE = -I includes  
OBJS = $(SRCS:.c=.o)
RM = rm -f

all: $(LIB_DIR)/libft.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIB_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_DIR)/libft.a:
	$(MAKE) -C $(LIB_DIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
