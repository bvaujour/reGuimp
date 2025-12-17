/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:46:39 by bvaujour          #+#    #+#             */
/*   Updated: 2022/11/17 14:53:44 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	big;

	big = n;
	if (big < 0)
	{
		ft_putchar_fd('-', fd);
		big = -big;
	}
	if (big / 10)
		ft_putnbr_fd(big / 10, fd);
	ft_putchar_fd(big % 10 + 48, fd);
}

/*int	main()
{
	int	nb;

	nb = -2147483648;
	ft_putnbr_fd(nb, 1);
}*/
