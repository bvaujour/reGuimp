/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mablatie <mablatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:31:53 by bvaujour          #+#    #+#             */
/*   Updated: 2023/08/18 16:35:49 by mablatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printchar(char c, int *len)
{
	write(1, &c, 1);
	*len += 1;
}

void	ft_printstr(const char *str, int *len)
{
	if (!str)
	{
		*len += write (1, "(null)", 6);
		return ;
	}
	*len += write (1, str, ft_strlen(str));
}

void	ft_address(void const *p, char *base, int *len, int token)
{
	unsigned long	size;
	unsigned long	nb;

	size = 0;
	while (base[size])
		size++;
	if (p)
	{
		if (token == 1)
			*len += write (1, "0x", 2);
		nb = (unsigned long)p;
		if (nb / size)
			ft_address((void *)(nb / size), base, len, 0);
		ft_printchar(base[nb % size], len);
	}
	else
		*len += write (1, "(nil)", 5);
}

void	ft_putnbr_base(long long int nbr, char *base, int *len)
{
	int	size;

	size = 0;
	while (base[size])
		size++;
	if (nbr < 0)
	{
		ft_printchar('-', len);
		nbr = -nbr;
	}
	if (nbr / size)
		ft_putnbr_base(nbr / size, base, len);
	ft_printchar(base[nbr % size], len);
}

int	format(char c, va_list ap)
{
	int	len;

	len = 0;
	if (c == '%')
		len += write (1, "%", 1);
	else if (c == 'c')
		ft_printchar(va_arg(ap, int), &len);
	else if (c == 's')
		ft_printstr(va_arg(ap, char *), &len);
	else if (c == 'p')
		ft_address(va_arg(ap, void *), "0123456789abcdef", &len, 1);
	else if (c == 'i' || c == 'd')
		ft_putnbr_base(va_arg(ap, int), "0123456789", &len);
	else if (c == 'u')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789", &len);
	else if (c == 'x')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef", &len);
	else if (c == 'X')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF", &len);
	return (len);
}
