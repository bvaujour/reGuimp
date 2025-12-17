/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:48:15 by bvaujour          #+#    #+#             */
/*   Updated: 2022/09/23 12:50:05 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	size_dest;
	unsigned int	size_src;
	unsigned int	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	size_dest = ft_strlen(dst);
	size_src = ft_strlen((char *)src);
	if (size <= size_dest)
		return (size + size_src);
	while (src[i] != '\0' && size_dest + i < size - 1)
	{
		dst[size_dest + i] = src[i];
		i++;
	}
	dst[size_dest + i] = '\0';
	return (size_dest + size_src);
}

/*#include <stdio.h>
#include <bsd/string.h>

int	main()
{
	char	src[50] = "hello world";
	char	dest[50] = ", salut le monde";
	printf("%s\n", src);
	printf("%s\n", dest);
	printf("%ld\n", ft_strlcat(dest, src, 30));
	printf("%ld\n", strlcat(dest, src, 30));
	printf("%s\n", src);
	printf("%s\n", dest);
	return (0);
}*/
