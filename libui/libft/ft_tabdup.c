/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanitas <vanitas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:13:23 by bvaujour          #+#    #+#             */
/*   Updated: 2023/08/21 16:04:38 by vanitas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab, char *more, int opt)
{
	int		i;
	char	**new;

	i = 0;
	while (tab[i])
		i++;
	if (more != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (tab[++i])
		new[i] = ft_strdup(tab[i]);
	if (more != NULL)
		new[i++] = ft_strdup(more);
	new[i] = 0;
	if (opt == 1)
		ft_free_tab(tab);
	return (new);
}

/*int main()
{
	char *tab[10];
	char *str = "bonjour";

	int i;
	i = 0;

	while (i < 10)
	{
		tab[i] = "hello";
		i++;
	}
	tab[i] = 0;
	char **new = ft_tabdup(tab, str);
	i = 0;
	while (new[i])
	{
		printf("%s\n", new[i]);
		i++;
	}
	ft_free_tab(new);
	
}*/
