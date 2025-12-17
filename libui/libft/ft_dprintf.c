/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mablatie <mablatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:15:03 by bvaujour          #+#    #+#             */
/*   Updated: 2023/08/24 16:47:48 by mablatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printchar_fd(int fd, char c, int *len)
{
	write(fd, &c, 1);
	*len += 1;
}

void	ft_printstr_fd(int fd, const char *str, int *len)
{
	if (!str)
	{
		*len += write (fd, "(null)", 6);
		return ;
	}
	*len += write(fd, str, ft_strlen(str));
}

void	ft_putnbr_base_fd(int fd, long long nbr, char *base, int *len)
{
	int	size;

	size = 0;
	while (base[size])
		size++;
	if (nbr < 0)
	{
		ft_printchar_fd(fd, '-', len);
		nbr = -nbr;
	}
	if (nbr / size)
		ft_putnbr_base_fd(fd, nbr / size, base, len);
	ft_printchar_fd(fd, base[nbr % size], len);
}

int	format_fd(int fd, char c, va_list ap)
{
	int	len;

	len = 0;
	if (c == '%')
		len += write (fd, "%", 1);
	else if (c == 'c')
		ft_printchar_fd(fd, va_arg(ap, int), &len);
	else if (c == 's')
		ft_printstr_fd(fd, va_arg(ap, char *), &len);
	else if (c == 'i' || c == 'd')
		ft_putnbr_base_fd(fd, va_arg(ap, int), "0123456789", &len);
	else if (c == 'u')
		ft_putnbr_base_fd(fd, va_arg(ap, unsigned int), "0123456789", &len);
	else if (c == 'x')
		ft_putnbr_base_fd(fd, va_arg(ap, unsigned int), HEX_MIN, &len);
	else if (c == 'X')
		ft_putnbr_base_fd(fd, va_arg(ap, unsigned int), HEX_MAJ, &len);
	return (len);
}

int	ft_dprintf(int fd, const char *str, ...)
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
		len += write (fd, str, i);
		if (str[i] == '%')
		{
			len += format_fd(fd, str[i + 1], ap);
			i += 2;
		}
		str += i;
	}
	va_end(ap);
	return (len);
}

/*int	main()
{
	char *str = "helloworld";

	ft_dprintf(2, "%s 12345\n", str);
}*/