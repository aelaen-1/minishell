/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <glabaden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:17:50 by lvastel           #+#    #+#             */
/*   Updated: 2024/12/13 13:17:52 by lvastel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_echo(char **argv)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	if (!argv[i])
		return (1);
	if (!ft_strcmp("-n", argv[i]))
	{
		n_option = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (n_option == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
