/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukezi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:23:01 by aboukezi          #+#    #+#             */
/*   Updated: 2024/01/11 16:23:02 by aboukezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*liste;

	if (lst && del)
	{
		while (*lst)
		{
			liste = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = liste;
		}
		*lst = NULL;
	}
}
/*  *lst = liste ==> 'nouvelle' lst sans le premier element, 
puis sans les deux premiers, etc.. jusqu'a tout supprimer*/
