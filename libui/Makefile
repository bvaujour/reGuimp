# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: injah <injah@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 16:48:10 by bvaujour          #+#    #+#              #
#    Updated: 2025/12/16 22:48:46 by injah            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libui.a

OBJ_DIR = obj

SRC =	ui_core.c						\
		ui_engine.c						\
		ui_binding.c					\
		ui_widget_user.c				\
		ui_widget.c						\
		ui_canvas.c						\
		ui_button.c						\
		ui_utils.c						\
		ui_drawable.c					\
		ui_slider.c						\

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CFLAGS = -Wall -Wextra -Werror -g -Ilibft

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