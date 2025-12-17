/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:33:03 by bvaujour          #+#    #+#             */
/*   Updated: 2022/11/23 20:15:15 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*void	del(void *content)
{
	char	*tmp;
	unsigned int	i;
	
	i = 0;
	tmp = (char *)content;
	while (i < ft_strlen(tmp))
	{
		tmp[i] = '7';
		i++;
	}
}

void	print_list(t_list *lst)
{
	while (lst)
	{
		ft_putstr_fd(lst->content, 1);
		lst = lst->next;
	}
}

int	main()
{
	t_list	*space1;
	t_list	*space2;

	char	str1[] = "gro";
	char	str2[] = "sse";

	space1 = ft_lstnew(str1);
	space2 = ft_lstnew(str2);
	print_list(space1);
	ft_lstadd_back(&space1, space2);
	ft_lstiter(space1, del);
	print_list(space1);
}*/
