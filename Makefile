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

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
LIBFT_DIR	= libft

# Source files
SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/parsing.c \
			  $(SRC_DIR)/path.c \
			  $(SRC_DIR)/process.c \
			  $(SRC_DIR)/utils.c

# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "Building libft"
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "pipex removed"

re: fclean all


.PHONY: all clean fclean re