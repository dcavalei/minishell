# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmartins <rmartins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/30 16:53:19 by rmartins          #+#    #+#              #
#    Updated: 2021/10/18 11:35:18 by rmartins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
LIBFT = libft/libft.a
CFLAGS = -Wall -Wextra -Werror -g
EXTRA_FLAGS = -lreadline
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

HEADER = $(shell find $(INC_DIR) -type f -name "*.h")
SRC = $(subst $(SRC_DIR)/,, $(shell find $(SRC_DIR) -type f -name "*.c"))


all: $(NAME)


resetprint:
	@echo $(ANSI_RESET)

$(NAME): $(OBJ) resetprint
	@echo $(ANSI_B_BGREEN) "compile libft" $(ANSI_RESET)$(ANSI_F_BBLACK)
	@$(MAKE) all -C libft
	@echo $(ANSI_RESET) ""
	@echo $(ANSI_B_BGREEN) "compile executable" $(ANSI_RESET)$(ANSI_F_BBLACK)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(EXTRA_FLAGS) -o $(NAME)
	@echo $(ANSI_RESET) ""

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	@echo $(ANSI_B_RED) "clean libft" $(ANSI_RESET)$(ANSI_F_BRED)
	@$(MAKE) clean -C libft
	rm -rf $(OBJ_DIR)
	@echo $(ANSI_RESET) ""

fclean: clean
	@echo $(ANSI_B_RED) "fclean" $(ANSI_RESET)$(ANSI_F_BRED)
	@$(MAKE) fclean -C libft
	rm -f $(NAME)
	rm -f $(NAME_S)
	@echo $(ANSI_RESET) ""

re: fclean all

.PHONY: all clean fclean


# colors
ANSI_RESET = "\033[0m"
ANSI_B_RED = "\033[41m"
ANSI_B_BGREEN = "\033[42;1m"
ANSI_F_BRED = "\033[31;1m"
ANSI_F_BBLACK = "\033[30;1m"


norm:
	@echo $(ANSI_B_RED) "norminette v3" $(ANSI_RESET)
	@norminette $(HEADER) \
		$(addprefix src/,$(SRC))

run: all
	@echo $(ANSI_B_RED) "Running for debbuger without sanitize" $(ANSI_RESET)
	./$(NAME)

runv: all
	@echo $(ANSI_B_RED) "Valgrind RESULT" $(ANSI_RESET)
	# valgrind -q --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) $(TEST_PARAMETERS)
	# valgrind --leak-check=full --show-leak-kinds=all -s ./$(NAME) $(TEST_PARAMETERS)
	# valgrind --leak-check=full -s ./$(NAME) $(TEST_PARAMETERS)
	valgrind ./$(NAME) $(TEST_PARAMETERS)

NAME_S = $(NAME)_sanitize
runs: all
	@echo $(ANSI_B_RED) "Running with sanitize" $(ANSI_RESET)
	$(CC) $(CFLAGS) -fsanitize=address $(OBJ) $(LIBFT) $(EXTRA_FLAGS) -o $(NAME_S)
	./$(NAME_S)