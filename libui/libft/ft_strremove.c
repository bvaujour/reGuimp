/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanitas <vanitas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:10:38 by bvaujour          #+#    #+#             */
/*   Updated: 2023/08/21 16:07:40 by vanitas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Remove the n'th occurence of to_del in src*/

static void	option(char *src, char *to_del, int opt)
{
	if (opt == 1)
		free(src);
	else if (opt == 2)
		free(to_del);
	else if (opt == 3)
	{
		free(src);
		free(to_del);
	}
}

char	*ft_strremove(char *src, char *to_del, int n, int opt)
{
	int		i;
	int		j;
	char	*new;

	if (!to_del || !*to_del || !src || !*src
		|| n < 0 || n > ft_countoccur(src, to_del))
	{
		option(src, to_del, opt);
		return (src);
	}
	new = malloc(sizeof(char) * (ft_strlen(src) - ft_strlen(to_del) + 1));
	if (!new)
		return (NULL);
	i = -1;
	j = ft_chrstrinstr(src, to_del, n);
	while (++i < j)
		new[i] = src[i];
	j += ft_strlen(to_del) - 1;
	while (src[++j])
		new[i++] = src[j];
	new[i] = '\0';
	option(src, to_del, opt);
	return (new);
}

// int main()
// {
//     char    *str = ft_strdup("ls | echo lol");
//     str = ft_strremove(str, "ls |", 1, 1);
//     str = ft_strremove(str, " echo lol", 1, 1);
//     free (str);
// }
