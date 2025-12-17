/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanitas <vanitas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:01 by bvaujour          #+#    #+#             */
/*   Updated: 2023/08/21 16:02:45 by vanitas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	ft_part(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static int	str_count(char *str, char c)
{
	int	i;
	int	sc;

	i = 0;
	sc = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			if (str[i + 1] == c || str[i + 1] == '\0')
				sc++;
			i++;
		}
	}
	return (sc);
}

static char	*ft_str(char **parts, char *str, char c)
{
	int		i;
	int		str_len;
	char	*dest;

	i = 0;
	str_len = ft_part(str, c);
	dest = malloc((str_len + 1) * sizeof(char));
	if (dest == 0)
		return (ft_free(parts));
	while (i < str_len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(const char *s, char c)
{
	char	**parts;
	int		i;

	if (!s)
		return (0);
	i = 0;
	parts = malloc(sizeof(char *) * (str_count((char *)s, c) + 1));
	if (parts == 0)
		return (0);
	while (*s != '\0')
	{
		while (s[0] == c && *s != '\0')
			s++;
		if (*s != '\0')
		{
			parts[i] = ft_str(parts, (char *)s, c);
			if (!parts[i])
				return (NULL);
			i++;
		}
		while (s[0] != c && *s != '\0')
			s++;
	}
	parts[i] = 0;
	return (parts);
}

/*int	main()
{
	char	str[] = "a aa aaa aaaa aaaaa";
	char	c = ' ';
	int	i;
	char	**tab = ft_split(str, c);
	i = 0;
	printf ("main %d\n", str_count(str, c));
	while (tab[i])
	{
		printf ("main str :%s\n", tab[i]);
		i++;
	}
	free(tab);
}*/
// 	return (0);
// }
