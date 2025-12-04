# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/20 09:45:35 by injah             #+#    #+#              #
#    Updated: 2025/10/07 10:47:51 by bvaujour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = guimp

SRC = main.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g		\
         -Ilibui						\
         -Ilibui/SDL/include/SDL2		\
         -Ilibui/SDL_ttf/include/SDL2	\
		 -Ilibui/SDL_ttf/freetype/include

LIBUI = -Llibui -lui 					\
        -Llibui/SDL/lib -lSDL2			\
        -Llibui/SDL_ttf/lib -lSDL2_ttf	\
		-Llibui/lib -lfreetype 			\
        -Llibui/SDL_image/lib -lSDL2_image	\
        -lm

CC = cc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C libui
	$(CC) $(CFLAGS) $(OBJ) $(LIBUI) -o $(NAME)

clean:
	make clean -C libui
	rm -f $(OBJ)

fclean: clean
	make fclean -C libui
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
