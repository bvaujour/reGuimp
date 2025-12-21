# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: injah <injah@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/20 09:45:35 by injah             #+#    #+#              #
#    Updated: 2025/12/20 07:00:11 by injah            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = guimp

SRC = main.c
OBJ = $(SRC:.c=.o)

CC = cc

# Flags de compilation
CFLAGS = -Wall -Wextra -Werror -g

# SDL via pkg-config (flags automatiques)
SDL_CFLAGS  = $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
SDL_LDFLAGS = $(shell pkg-config --libs   sdl2 SDL2_image SDL2_ttf)

# Libs du projet
LIBUI_DIR = libui
LIBUI_LIB = -L$(LIBUI_DIR) -lui
LIBFT_LIB = -L$(LIBUI_DIR)/libft -lft

# Flags de linkage finaux
LDFLAGS = $(LIBUI_LIB) $(LIBFT_LIB) $(SDL_LDFLAGS) -lm

# Règle de compilation
%.o: %.c
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBUI_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	make clean -C $(LIBUI_DIR)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBUI_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

