/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:47:41 by bvaujour          #+#    #+#             */
/*   Updated: 2022/11/09 16:49:33 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int		i;
	const unsigned char	*tmpsrc;
	unsigned char		*tmpdest;

	tmpsrc = src;
	tmpdest = dest;
	i = -1;
	if (!dest && !src)
		return (0);
	if (tmpsrc < tmpdest)
	{
		while (n != 0)
		{
			tmpdest[n - 1] = tmpsrc[n - 1];
			n--;
		}
	}
	else
		while (++i < n)
			tmpdest[i] = tmpsrc[i];
	return (dest);
}

/*int	main(void)
{
	char	str1[] = "agmo";
	//char	str2[] = "beber";

	ft_memmove(str1 + 3, str1, 1);
	printf("%s\n", str1);
	
	return (0);
}*/
