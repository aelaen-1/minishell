/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukezi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:33:35 by aboukezi          #+#    #+#             */
/*   Updated: 2023/12/13 12:33:36 by aboukezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*image;

	if (!s || !*f)
		return (NULL);
	len = ft_strlen(s);
	image = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!image)
		return (NULL);
	i = 0;
	while (s[i])
	{
		image[i] = f(i, s[i]);
		i++;
	}
	image[i] = '\0';
	return (image);
}
