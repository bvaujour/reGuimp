/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrstrinstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mablatie <mablatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:44:28 by bvaujour          #+#    #+#             */
/*   Updated: 2023/08/18 16:37:31 by mablatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* send a int to the first char of to_chr of the n time to_chr was found in src
    return -1 in case of error*/

int	ft_chrstrinstr(char *src, char *to_chr, int n)
{
	int	i;
	int	j;

	i = 0;
	if (n > ft_countoccur(src, to_chr) || n <= 0 || !src || !to_chr)
		return (-1);
	while (n && src[i])
	{
		j = 0;
		while (src[i] == to_chr[j] && src[i] && to_chr[j])
		{
			i++;
			j++;
		}
		if (to_chr[j] == '\0')
			n--;
		if (!n || !src[i])
			break ;
		i++;
	}
	return (i - ft_strlen(to_chr));
}

/*int main()
{
	    char    *src = "<in <out<in";
        char    *to_del = "<in";
    
        int removed = ft_chrstrinstr(src, to_del, 1);
        printf("chr = %d\n", removed);
}*/
