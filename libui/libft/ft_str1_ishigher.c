/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str1_ishigher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanitas <vanitas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:10:01 by bvaujour          #+#    #+#             */
/*   Updated: 2023/08/21 16:08:41 by vanitas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_len(char *str1, char *str2)
{
	if (str1[0] == '-' && (str2[0] == '+'
			|| (str2[0] >= '0' && str2[0] <= '9')))
		return (0);
	else if ((str1[0] == '+'
			|| (str1[0] >= '0' && str1[0] <= '9')) && str2[0] == '-')
		return (1);
	if (ft_strlen(str1) > ft_strlen(str2) && str1[0] == '-')
		return (0);
	else if (ft_strlen(str1) > ft_strlen(str2))
		return (1);
	return (-1);
}

int	ft_str1_ishigher(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (check_len(str1, str2) != -1)
		return (check_len(str1, str2));
	while (str1[i] && str2[2] && str1[0] == '-')
	{
		if (str1[i] > str2[i])
			return (0);
		else if (str1[i] < str2[i])
			return (1);
		i++;
	}
	if (i != 0)
		return (-1);
	while (str1[i] && str2[2])
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (0);
		i++;
	}
	return (-1);
}
