/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukezi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:23:58 by aboukezi          #+#    #+#             */
/*   Updated: 2024/01/11 16:23:59 by aboukezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*dup;

	dup = (t_list *)malloc(sizeof(t_list));
	if (!dup)
		return (NULL);
	dup->content = content;
	dup->next = NULL;
	return (dup);
}
/* dup->content = (*dup).content = content*/
