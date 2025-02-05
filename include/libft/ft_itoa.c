/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukezi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:33:14 by aboukezi          #+#    #+#             */
/*   Updated: 2023/12/13 12:33:17 by aboukezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	wordlen(int n)
{
	unsigned int	len;

	len = 0;
	if (n <= 0)
	{
		if (n == 0)
			return (1);
		n *= -1;
		len = 1;
	}
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*converted;
	unsigned int	sign;
	unsigned int	len;
	long long int	nb;

	nb = n;
	len = wordlen(nb);
	sign = 0;
	converted = (char *)malloc(sizeof(char) * (len + 1));
	if (!converted)
		return (NULL);
	converted[len] = '\0';
	if (nb < 0)
	{
		sign = 1;
		converted[0] = '-';
		nb *= -1;
	}
	while (len > sign)
	{
		converted[len - 1] = (nb % 10) + 48;
		nb = nb / 10;
		len--;
	}
	return (converted);
}
