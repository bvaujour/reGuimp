/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:34:03 by bvaujour          #+#    #+#             */
/*   Updated: 2025/05/15 00:41:06 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>

char	*ft_gnljoin(char *save, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!save)
	{
		save = (char *)malloc(1 * sizeof(char));
		if (!save)
			return (NULL);
		save[0] = '\0';
	}
	if (!save || !buff)
		return (NULL);
	str = malloc(sizeof(char) * (ft_gnllen(save) + ft_gnllen(buff) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (save[++i] != '\0')
		str[i] = save[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	free(save);
	return (str);
}

char	*ft_get_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line || !save)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_new_save(char *save)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_gnllen(save) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		str[j++] = save[i++];
	str[j] = '\0';
	free(save);
	return (str);
}

char	*ft_read_to_save(int fd, char *save)
{
	char	*buff;
	int		ret;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	ret = 1;
	while (!ft_gnlchr(save, '\n') && ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[ret] = '\0';
		save = ft_gnljoin(save, buff);
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save = NULL;

	if (fd == FREE_STATIC)
	{
		free (save);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = ft_read_to_save(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	save = ft_new_save(save);
	return (line);
}

/*int	main(int argc, char **argv)
{
	int	fd1;
	char	*str1;
	(void)argc;
	int	i;
	
	fd1 = open("texte.txt", O_RDONLY);
	
	i = 0;
	while (i < atoi(argv[1]))
	{
		str1 = get_next_line(fd1);
		printf("%s", str1);
		free(str1);
		i++;
	}
	return(0);
}*/
