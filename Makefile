NAME = minishell
CC = gcc
CFLAGS = -g -I includes -lreadline 
SRCS = src/exec/exec.c src/utils/utils.c src/main.c
LIB_DIR = src/libft 
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
