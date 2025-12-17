/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mablatie <mablatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:58:47 by bvaujour          #+#    #+#             */
/*   Updated: 2023/08/18 16:44:15 by mablatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (dest == 0)
		return (0);
	ft_strcpy(dest, (char *)s);
	return (dest);
}

/*int	main()
{
	char src[] = "testestestestestste";
	char *dest;
	
	dest = ft_strdup(src);
	printf ("%s", dest);
	free(dest);
	return (0);
}*/
