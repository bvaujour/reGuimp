/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:03:03 by bvaujour          #+#    #+#             */
/*   Updated: 2025/05/27 09:17:13 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define FREE_STATIC -99

char	*ft_gnljoin(char *left_str, char *buff);
char	*ft_get_line(char *str);
char	*get_next_line(int fd);
size_t	ft_gnllen(char *s);
char	*ft_gnlchr(char *s, int c);

#endif
