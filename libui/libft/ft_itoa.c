/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanitas <vanitas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:20:50 by bvaujour          #+#    #+#             */
/*   Updated: 2023/08/21 16:03:07 by vanitas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intcount(long int n)
{
	int	i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		sign;
	int		len;

	sign = 1;
	len = intcount(n);
	tab = malloc(sizeof(char) * (len + 1));
	if (tab == NULL)
		return (NULL);
	tab[len] = '\0';
	if (n == 0)
		tab[0] = 48;
	if (n < 0)
	{
		tab[0] = '-';
		sign = -1;
	}
	while (n != 0)
	{
		tab[len - 1] = ((n % 10) * sign) + 48;
		n = n / 10;
		len--;
	}
	return (tab);
}

/*int	main()
{
	int	n;

	n = -2147483648;
	printf ("itoa = %s\n", ft_itoa(n));
	printf("%d\n", intcount(n));
	return (0);
}*/
