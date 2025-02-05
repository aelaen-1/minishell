/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukezi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:35:42 by aboukezi          #+#    #+#             */
/*   Updated: 2024/01/08 11:35:43 by aboukezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*space;
	size_t	i;

	if (nmemb && size && nmemb > ((size_t) -1 / size))
		return (NULL);
	i = 0;
	space = malloc(nmemb * size);
	if (!space)
		return (NULL);
	while (i < (nmemb * size))
	{
		*(unsigned char *)(space + i) = 0;
		i++;
	}
	return (space);
}
