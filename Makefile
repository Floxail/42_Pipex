# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 26/12/2025 06:52:32 by flvejux           #+#    #+#              #
#    Updated: 26/12/2025 06:52:32 by flvejux          ###   ########.ch        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
NAME_BONUS	= pipex_bonus

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
OBJ_DIR_BONUS = obj_bonus
LIBFT_DIR	= libft

# Source files
SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/parsing.c \
			  $(SRC_DIR)/path.c \
			  $(SRC_DIR)/process.c \
			  $(SRC_DIR)/utils.c

SRCS_BONUS	= main_bonus.c \
			  parsing_bonus.c \
			  path_bonus.c \
			  process_bonus.c \
			  utils_bonus.c \
			  get_herdoc_bonus.c

# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS	= $(SRCS_BONUS:%.c=$(OBJ_DIR_BONUS)/%.o)

# Libraries
LIBFT		= $(LIBFT_DIR)/libft.a

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I. -I$(LIBFT_DIR)
LDFLAGS		= -L$(LIBFT_DIR) -lft

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "compiled successfully"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled"

$(OBJ_DIR_BONUS)/%.o: %.c | $(OBJ_DIR_BONUS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled bonus"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR_BONUS):
	@mkdir -p $(OBJ_DIR_BONUS)

$(LIBFT):
	@echo "Building libft"
	@$(MAKE) -C $(LIBFT_DIR)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LDFLAGS) -o $(NAME_BONUS)
	@echo "pipex_bonus compiled successfully"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@echo "Object files removed"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "pipex and pipex_bonus removed"

re: fclean all


.PHONY: all bonus clean fclean re