# **************************************************************************** #
# COLORS #
# **************************************************************************** #
BLACK    = \033[0;30m
RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
BLUE     = \033[0;34m
PURPLE   = \033[0;35m
CYAN     = \033[0;36m
WHITE    = \033[0;37m
RESET    = \033[0m
BOLD     = \033[1m
CLEAR    = \r\033[K

# **************************************************************************** #
# VARIABLES #
# **************************************************************************** #
NAME        = libft.a
CC          = clang
CFLAGS      = -Wall -Wextra -Werror
INC_PATH    = .
SRC_PATH    = src
OBJ_PATH    = obj

SRC_FILES   = ft_atoi.c ft_isalnum.c ft_isalpha.c \
              ft_isascii.c ft_isdigit.c ft_isprint.c ft_strchr.c \
              ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
              ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strstr.c \
              ft_tolower.c ft_toupper.c ft_memset.c ft_bzero.c \
              ft_memcpy.c ft_memmove.c ft_memcmp.c ft_calloc.c \
              ft_memchr.c ft_putchar_fd.c ft_putstr_fd.c \
              ft_putnbr_fd.c ft_putendl_fd.c ft_itoa.c \
              ft_strtrim.c ft_split.c ft_strjoin.c ft_substr.c \
              ft_striteri.c ft_strmapi.c ft_isspace.c ft_strndup.c \
              ft_strcmp.c ft_strcpy.c ft_strncpy.c ft_strcat.c

BONUS_FILES = ft_lstnew.c ft_lstadd_front.c \
              ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
              ft_lstclear.c

SRCS        = $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_PATH)/, $(SRC_FILES:.c=.o))
BONUS_SRCS  = $(addprefix $(SRC_PATH)/, $(BONUS_FILES))
BONUS_OBJS  = $(addprefix $(OBJ_PATH)/, $(BONUS_FILES:.c=.o))

TOTAL_FILES = $(words $(SRC_FILES))
CURR_FILE   = 0

# **************************************************************************** #
# RULES #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(YELLOW)Creating library archive...$(RESET)\n"
	@ar rcs $@ $^
	@printf "$(GREEN)Library $(BOLD)$(NAME)$(RESET)$(GREEN) created successfully!$(RESET)\n"

bonus: $(BONUS_OBJS)
	@printf "$(YELLOW)Adding bonus functions to library...$(RESET)\n"
	@ar rcs $(NAME) $^
	@printf "$(GREEN)Bonus functions added to $(BOLD)$(NAME)$(RESET)$(GREEN)!$(RESET)\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(eval CURR_FILE=$(shell echo $$(($(CURR_FILE)+1))))
	@printf "$(CLEAR)$(BLUE)Compiling: $(WHITE)$(notdir $<)$(RESET) "
	@printf "$(PURPLE)[$(CURR_FILE)/$(TOTAL_FILES)]$(RESET)"
	@$(CC) $(CFLAGS) -I$(INC_PATH) -o $@ -c $<

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@printf "$(BLUE)Created objects directory$(RESET)\n"

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@rm -rf $(OBJ_PATH)
	@printf "$(GREEN)Clean complete!$(RESET)\n"

fclean: clean
	@printf "$(RED)Removing library...$(RESET)\n"
	@rm -f $(NAME)
	@printf "$(GREEN)Full clean complete!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re bonus