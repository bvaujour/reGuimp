/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:43:12 by bvaujour          #+#    #+#             */
/*   Updated: 2022/11/11 14:43:15 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (tmps1[i] - tmps2[i] != 0)
			return (tmps1[i] - tmps2[i]);
		i++;
	}
	return (0);
}

/*int	main()
{
	char s[] = {-128, 0, 124, 0};
	//char sCpy[] = {-128, 0, 127, 0};
	char s2[] = {0, 0, 127, 0};
	//char s3[] = {0, 0, 42, 0};
	
	printf ("%d\n", ft_memcmp (s, s2, 1));
	printf ("%d\n", memcmp (s, s2, 1));
}*/
