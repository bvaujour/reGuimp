/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:24:07 by bvaujour          #+#    #+#             */
/*   Updated: 2022/11/24 14:24:26 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;

	if (!f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		new_elem = ft_lstnew(f(lst->content));
		if (new_elem == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_elem);
		lst = lst->next;
	}
	return (new_lst);
}

/*void	del(void *content)
{
	char	*tmp;
	unsigned int	i;
	
	i = 0;
	tmp = (char *)content;
	while (i < ft_strlen(tmp))
	{
		tmp[i] = '\0';
		i++;
	}
}

void	*f (void * p)
{
	void *r = malloc(sizeof(int));
	*(int*)r = *(int*)p + 1; 
	return (r);
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
	t_list	*new;

	char	str1[] = "1";
	char	str2[] = "2";

	space1 = ft_lstnew(str1);
	space2 = ft_lstnew(str2);
	//print_list(space1);
	ft_lstadd_back(&space1, space2);
	//print_list(space1);
	new = ft_lstmap(space1, f, del);
	print_list(new);
}*/
