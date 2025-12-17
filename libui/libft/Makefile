# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: injah <injah@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 12:35:11 by bvaujour          #+#    #+#              #
#    Updated: 2025/05/15 09:47:12 by injah            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_free_tab.c ft_str1_ishigher.c ft_atol.c ft_atoll.c ft_strremoveall.c ft_strndup.c ft_strremove.c ft_countoccur.c ft_chrstrinstr.c ft_tabdup.c ft_strcmp.c ft_bzero.c ft_dprintf.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_printf.c convertion.c get_next_line.c get_next_line_utils.c ft_stock_file.c

SRC_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ_BONUS = $(SRC_BONUS:.c=.o)

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Werror -Wextra -g3

all : $(NAME)

%.o: %.c
	@cc $(FLAG) -c $< -o $@
	@printf "Compiling libft files.....%-50s \r" $@

$(NAME) : $(OBJ) libft.h bonus
	@ar -rcs $(NAME) $(OBJ)

bonus: $(OBJ_BONUS) $(OBJ)
	@ar -rcs $(NAME) $(OBJ_BONUS) $(OBJ)

clean:
	@rm -rf $(OBJ) $(OBJ_BONUS) ./a.out

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
