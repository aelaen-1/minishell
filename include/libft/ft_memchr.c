/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukezi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:37:48 by aboukezi          #+#    #+#             */
/*   Updated: 2024/01/08 11:37:49 by aboukezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*str;

	str = (const char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
