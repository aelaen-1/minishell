/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:38:10 by aboukezi          #+#    #+#             */
/*   Updated: 2024/12/12 00:30:15 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if (d == NULL && s == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(d + i) = *(s + i);
		i++;
	}
	return (d);
}
