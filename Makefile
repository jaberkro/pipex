# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jaberkro <jaberkro@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/14 12:14:46 by jaberkro      #+#    #+#                  #
#    Updated: 2022/05/21 16:35:28 by jaberkro      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = pipex
FLAGS = -Wall -Wextra -Werror -g
INC = -I ./libft -I ./include

LIBFT_DIR = libft/
LIBFT = libft/libft.a

SRC_DIR = src
BUILD_DIR = obj

SRC = src/main.c src/init.c src/paths.c src/close.c

SRC_BONUS = src/main_bonus.c src/init_bonus.c src/paths_bonus.c \
	src/close_bonus.c

ifdef WITH_BONUS
OBJ = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC_BONUS:.c=.o))
else
OBJ = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC:.c=.o))
endif

# COLORS
PINK	= \x1b[35m
BLUE	= \x1b[34m
YELLOW	= \x1b[33m
GREEN	= \x1b[32m
RED		= \x1b[31m
RESET	= \x1b[0m

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	CC $(FLAGS) $(INC) -c $^ -o $@

$(NAME): $(LIBFT) $(OBJ)
	cp $(LIBFT) ./$(NAME)
	CC $(FLAGS) $(OBJ) $(LIBFT) $(INC) -o $(NAME)
	@echo "$(RED)Done $(GREEN)COM$(YELLOW)PI$(BLUE)LING $(PINK)PIPEX$(RESET):)"

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

bonus:
	$(MAKE) WITH_BONUS=1 all

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)Done $(GREEN)CLEANING$(YELLOW) PIPEX$(PINK) :)$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(RED)Done $(GREEN)FANCY CLEANING$(YELLOW) PIPEX$(PINK) :)$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
