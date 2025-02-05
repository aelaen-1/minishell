/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukezi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:23:44 by aboukezi          #+#    #+#             */
/*   Updated: 2024/01/11 16:23:45 by aboukezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*liste;
	t_list	*newcontent;

	if (!lst || !f || !del)
		return (NULL);
	liste = NULL;
	while (lst)
	{
		newcontent = ft_lstnew(f(lst->content));
		if (!newcontent)
		{
			ft_lstclear(&liste, del);
			return (NULL);
		}
		ft_lstadd_back(&liste, newcontent);
		lst = lst->next;
	}
	return (liste);
}
