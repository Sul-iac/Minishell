# **************************************************************************** #
# COLORS #
# **************************************************************************** #

BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m
BOLD = \033[1m
CLEAR = \r\033[K

# **************************************************************************** #
# VARIABLES #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I includes -I src/libft
AUTHORS = qbarron and tgeradi

PARSE_SRC =	expenser.c expenser_2.c free_parsing.c \
			lexer.c lexer_2.c lexer_3.c lexer_4.c lexer_5.c \
			parser.c parser_2.c parser_3.c

BUILTIN_SRC = cd.c echo.c env.c exit.c export.c pwd.c unset.c export_utils.c

EXEC_SRC =	exec.c pipes.c redirs.c utils.c free_utils.c \
			free_pipes.c heredoc.c redirs2.c signal_heredoc_handler.c \
			pipes2.c main_prompt1.c main_prompt2.c clean_all_1.c get_path.c

MAIN_SRC = main.c

SRCS = $(addprefix src/parsing/, $(PARSE_SRC)) \
       $(addprefix src/builtin/, $(BUILTIN_SRC)) \
       $(addprefix src/exec/, $(EXEC_SRC)) \
       $(addprefix src/, $(MAIN_SRC))

OBJ_DIR = objs
OBJ_SUBDIRS = $(OBJ_DIR)/parsing $(OBJ_DIR)/builtin $(OBJ_DIR)/exec $(OBJ_DIR)
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = src/libft
LIBFT = $(LIBFT_DIR)/libft.a
TOTAL_FILES = $(words $(SRCS))
CURR_FILE = 0

# **************************************************************************** #
# RULES #
# **************************************************************************** #

all: logo $(OBJ_DIR) $(LIBFT) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_SUBDIRS)

logo:
	@printf "$(CYAN)"
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@printf "$(RESET)"
	@printf "\n$(BOLD)$(GREEN)By: $(AUTHORS)$(RESET)\n"

$(LIBFT):
	@printf "$(YELLOW)Building libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@printf "$(GREEN)Libft ready!$(RESET)\n"

$(NAME): $(OBJS)
	@printf "\n$(YELLOW)Linking objects into executable...$(RESET)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline
	@printf "$(GREEN)$(BOLD)$(NAME) is ready!$(RESET)\n"

$(OBJ_DIR)/%.o: src/%.c
	@$(eval CURR_FILE=$(shell echo $$(($(CURR_FILE)+1))))
	@printf "$(CLEAR)$(BLUE)Compiling: $(WHITE)$(notdir $<)$(RESET) "
	@printf "$(PURPLE)[$(CURR_FILE)/$(TOTAL_FILES)]$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@printf "$(GREEN)Clean complete!$(RESET)\n"

fclean: clean
	@printf "$(RED)Removing executable and libraries...$(RESET)\n"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@printf "$(GREEN)Full clean complete!$(RESET)\n\n"

re: fclean all

debug: CFLAGS += -fsanitize=address
debug: re

help:
	@printf "$(BOLD)Available commands:$(RESET)\n"
	@printf "$(CYAN)make$(RESET) - Build minishell\n"
	@printf "$(CYAN)make clean$(RESET) - Remove object files\n"
	@printf "$(CYAN)make fclean$(RESET) - Remove object files and executable\n"
	@printf "$(CYAN)make re$(RESET) - Rebuild from scratch\n"
	@printf "$(CYAN)make debug$(RESET) - Build with address sanitizer\n"
	@printf "$(CYAN)make help$(RESET) - Show this help message\n"

.PHONY: all clean fclean re logo help debug