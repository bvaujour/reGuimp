# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: injah <injah@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 16:48:10 by bvaujour          #+#    #+#              #
#    Updated: 2026/01/06 12:00:26 by injah            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libui.a

OBJ_DIR = obj

SRC =	ui_core.c						\
		ui_engine.c						\
		ui_widget_user.c				\
		ui_widget.c						\
		ui_window.c						\
		ui_utils.c						\
		ui_button.c						\
		ui_button_user.c				\
		ui_slider.c						\
		ui_slider_user.c				\
		ui_drawable.c					\
		ui_drawable_user.c				\
		ui_drawable_utils.c				\
		ui_box.c						\
		ui_dragbox.c					\

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

SDL_CFLAGS = $(shell pkg-config --cflags sdl2)

CFLAGS = -Wall -Wextra -Werror -g -Ilibft $(SDL_CFLAGS) -ISDL_ttf/include/SDL2 -ISDL_image/include/SDL2

CC = cc

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	ar -rcs  $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re