/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:21:00 by bvaujour          #+#    #+#             */
/*   Updated: 2023/06/09 18:38:57 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	ap;

	i = 0;
	len = 0;
	va_start(ap, str);
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != '%')
			i++;
		len += write (1, str, i);
		if (str[i] == '%')
		{
			len += format(str[i + 1], ap);
			i += 2;
		}
		str += i;
	}
	va_end(ap);
	return (len);
}

/*#include <stdio.h>

int	main()
{
	char	*str = "hello";
	//char	c = 'c';
	//int	a = 158520558;
	//void	*p = 0;
	//void	*t = 0;
	//ft_printf ("retour de ft_printf = %d\n", ft_printf("%x\n", a));
	//printf ("retour de printf = %d\n", printf("%x\n", a));
	//printf ("%c\n", str[0]);
	//ft_printf ("%c\n", str[0]);
	//ft_printf (" NULL %s NULL ", NULL);
	//printf (" NULL %s NULL ", str);
	//return (0);
	//ft_printf ("%p %p\n", p, t);
	ft_printf ("%p\n", str);
	ft_printf ("%p\n", str);
	//ft_printf(" %s %s %s %s %s ", " - ", "", "4", "", "2 ");
	//printf(" %s %s %s %s %s ", " - ", "", "4", "", "2 ");
	//printf(" %u ", -1);
	//ft_printf("%d\n", ft_printf(" %x ", -1));
}*/
