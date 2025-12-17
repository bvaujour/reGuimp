/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:57:04 by bvaujour          #+#    #+#             */
/*   Updated: 2022/11/09 16:13:38 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int		i;
	const char			*tmpsrc;
	char				*tmpdest;

	tmpsrc = src;
	tmpdest = dest;
	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		tmpdest[i] = tmpsrc[i];
		i++;
	}
	return (dest);
}

/*#include <stdio.h>

int	main(void)
{
	char	str1[] = "";
	char	str2[] = "";

	ft_memcpy(str1, str2, 5);
	printf("%s\n", str1);
	memcpy(str1, str2, 1);
	printf("%s\n", str1);
	
	return (0);
}*/
