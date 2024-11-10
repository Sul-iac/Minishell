# Colors
BLUE		= \033[0;34m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RESET		= \033[0m
CLEAR		= \r\033[K

# Variables
NAME		= libft.a
CC			= clang
CFLAGS		= -Wall -Wextra -Werror
INC_PATH	= .
SRC_PATH	= .
OBJ_PATH	= obj

# Source files
SRC_FILES	= ft_atoi.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_strchr.c \
			ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
			ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strstr.c \
			ft_tolower.c ft_toupper.c ft_memset.c ft_bzero.c \
			ft_memcpy.c ft_memmove.c ft_memcmp.c ft_calloc.c \
			ft_memchr.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putnbr_fd.c ft_putendl_fd.c ft_itoa.c \
			ft_strtrim.c ft_split.c ft_strjoin.c ft_substr.c \
			ft_striteri.c ft_strmapi.c ft_isspace.c ft_strndup.c \
			ft_strcmp.c

BONUS_FILES	= ft_lstnew.c ft_lstadd_front.c \
			ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c

# Paths
SRCS		= $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_PATH)/, $(SRC_FILES:.c=.o))
BONUS_SRCS	= $(addprefix $(SRC_PATH)/, $(BONUS_FILES))
BONUS_OBJS	= $(addprefix $(OBJ_PATH)/, $(BONUS_FILES:.c=.o))

# Progress counter
TOTAL_FILES	= $(words $(SRC_FILES))
CURR_FILE	= 0

# Rules
.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(YELLOW)Creating libft archive...$(RESET)"
	@ar rcs $@ $^
	@printf "$(CLEAR)$(GREEN)Libft archive created successfully!$(RESET)\n"

bonus: $(BONUS_OBJS)
	@printf "$(YELLOW)Adding bonus to libft...$(RESET)"
	@ar rcs $(NAME) $^
	@printf "$(CLEAR)$(GREEN)Bonus functions added to libft!$(RESET)\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(eval CURR_FILE=$(shell echo $$(($(CURR_FILE)+1))))
	@printf "$(CLEAR)$(BLUE)Compiling libft: $(RESET)$(notdir $<) [$(CURR_FILE)/$(TOTAL_FILES)]"
	@$(CC) $(CFLAGS) -I$(INC_PATH) -o $@ -c $<

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

clean:
	@printf "$(YELLOW)Cleaning libft objects...$(RESET)"
	@rm -rf $(OBJ_PATH)
	@printf "$(CLEAR)$(GREEN)Libft objects cleaned!$(RESET)\n"

fclean: clean
	@printf "$(YELLOW)Removing libft archive...$(RESET)"
	@rm -f $(NAME)
	@printf "$(CLEAR)$(GREEN)Libft fully cleaned!$(RESET)\n"

re: fclean all