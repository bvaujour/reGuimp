/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:13:26 by bvaujour          #+#    #+#             */
/*   Updated: 2023/06/20 19:19:08 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_cs(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	forward(char *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && in_cs(s1[i], set))
		i++;
	return (i);
}

static int	back(char *s1, const char *set)
{
	size_t	j;

	j = ft_strlen(s1) - 1;
	while (j > 0 && in_cs(s1[j], set) == 1)
		j--;
	return (j);
}

char	*ft_strtrim(char *s1, char const *set, int option)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*strim;

	if (!s1 || !set || !*s1 || !*set)
		return (s1);
	i = forward(s1, set);
	j = back(s1, set);
	k = 0;
	if (!s1[i])
	{
		if (option == 1)
			free(s1);
		return (ft_strdup(""));
	}
	strim = malloc (sizeof(char) * (j - i + 2));
	if (strim == 0)
		return (0);
	while (i <= j)
		strim[k++] = s1[i++];
	strim[k] = '\0';
	if (option == 1)
		free(s1);
	return ((char *)strim);
}

/*int	main()
{
	char	*str = "      g   ls ";
	//char	*str2 = "tripouille";
	//char	*set = "123";
	//str = str + 2;
	printf ("%s\n", ft_strtrim(str, " ", 0));
	//printf ("%ld\n", strlen(str2));
	//printf ("%s\n", str);
}*/
