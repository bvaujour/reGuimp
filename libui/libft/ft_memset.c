/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:13:31 by bvaujour          #+#    #+#             */
/*   Updated: 2022/11/09 13:20:03 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*tmp;

	tmp = (char *)s;
	i = 0;
	while (i < n)
	{
		tmp[i] = c;
		i++;
	}
	return (s);
}

/*int	main()
{
	int	str[10] = {0};
	
	printf("%d\n", str[0]);
	//ft_memset(str, 48, 8);
	memset(str, 30, 1);
	printf("%d\n", str[0]);
	//printf("%ls\n", str);
	
	printf("%d\n", str[1]);
	//printf("%ls\n", str);
	return (0);
}*/
