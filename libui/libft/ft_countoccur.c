/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countoccur.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanitas <vanitas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:33:32 by bvaujour          #+#    #+#             */
/*   Updated: 2023/08/21 16:15:13 by vanitas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*return the x time you found occurence of to_count in src*/
#include "libft.h"

static int	chr_in(char *src, char *to_count, int begin)
{
	int	i;
	int	j;

	i = -1;
	while (src[++i])
	{
		j = 0;
		while (src[i] == to_count[j])
		{
			i++;
			j++;
			if (!to_count[j])
				return (i - ft_strlen(to_count) + begin);
		}
		if (!src[i])
			break ;
	}
	return (-1);
}

int	ft_countoccur(char *src, char *to_count)
{
	int	go_to;
	int	i;
	int	x;

	x = 0;
	i = 0;
	go_to = chr_in(src + i, to_count, i);
	while (go_to != -1)
	{
		i = ft_strlen(to_count) + go_to;
		x++;
		go_to = chr_in(src + i, to_count, i);
	}
	return (x);
}
