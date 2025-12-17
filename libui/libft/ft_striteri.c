/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:40:57 by bvaujour          #+#    #+#             */
/*   Updated: 2022/11/17 15:44:58 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;
	int	len;

	i = 0;
	if (s != 0 && f != 0)
	{
		len = ft_strlen(s);
		while (i < len)
		{
			(*f)(i, s);
			s++;
			i++;
		}
	}
}

/*void ft_printchar(unsigned int i, char *str)
{
	str[i] = 0;
	printf("%c\n", str[i]);
}

int main(void)
{
	char str[] = "123456789";
	ft_striteri(str, ft_printchar);
	return (0);
}*/
