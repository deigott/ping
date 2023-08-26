# Color codes for better output
COLOR_RESET=\033[0m
COLOR_RED=\033[31m
COLOR_GREEN=\033[32m
COLOR_YELLOW=\033[33m
COLOR_BLUE=\033[34m

# Compilation flags and variables
FLAGS=-Wall -Werror -Wextra -fsanitize=address -g
CC=gcc
EXEC_NAME=ft_ping
SRCS=srcs/main.c srcs/parsing/parse_clo.c srcs/handle_errors.c srcs/icmp_utils.c srcs/handle_time.c srcs/libft.c
INCLUDES=includes/
IP_ADDRESS := $(shell ip addr | grep "enp1s0" | grep inet | cut -d ' ' -f6 | cut -d '/' -f1)
IP := $(echo "HEHLLO")

all: $(EXEC_NAME)

$(EXEC_NAME): $(SRCS)
	@$(CC) $(FLAGS) $(SRCS) -D SRC_ADDRESS=\"10.0.2.15\" -I $(INCLUDES) -o $(EXEC_NAME)
	@echo "$(COLOR_BLUE)$(EXEC_NAME) executable created$(COLOR_RESET)"

clean:
	@rm -rf $(EXEC_NAME)
	@echo "$(COLOR_YELLOW)Cleaned up the generated files$(COLOR_RESET)"

fclean: clean

re: fclean all

.PHONY: all clean fclean re
