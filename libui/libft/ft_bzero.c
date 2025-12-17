/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:43:36 by bvaujour          #+#    #+#             */
/*   Updated: 2022/11/09 14:50:58 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*tmp;
	size_t	i;

	tmp = s;
	i = 0;
	while (i < n)
	{
		tmp[i] = '\0';
		i++;
	}
}

/*int	main()
{
	char	str1[50] = "hello wolrd";
	char	str2[50] = "hello world";

	printf("%s\n", str1);
	bzero(str1, 50);
	printf("%s\n", str1);
	printf("%s\n", str2);
	ft_bzero(str2, 50);
	printf("%s\n", str2);
	return (0);
}*/
