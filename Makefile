# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: injah <injah@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/20 09:45:35 by injah             #+#    #+#              #
#    Updated: 2026/01/12 17:38:55 by injah            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = guimp

SRC = main.c draws_with_guimp.c draws_with_libui.c utils.c build.c
OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SDL_CFLAGS  = $(shell pkg-config --cflags sdl2) -Ilibui/SDL_ttf/include/SDL2 -Ilibui/SDL_ttf/freetype/include
SDL_LDFLAGS = $(shell pkg-config --libs sdl2)  -Llibui/SDL_ttf/lib -lSDL2_ttf -Llibui/lib -lfreetype -Llibui/SDL_image/lib -lSDL2_image

LIBUI_DIR = libui
LIBUI_LIB = -L$(LIBUI_DIR) -lui
LIBFT_LIB = -L$(LIBUI_DIR)/libft -lft

LDFLAGS = $(LIBUI_LIB) $(LIBFT_LIB) $(SDL_LDFLAGS) -lm

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

