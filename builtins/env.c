/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvastel <lvastel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:17:57 by lvastel           #+#    #+#             */
/*   Updated: 2024/12/13 13:18:00 by lvastel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_env(t_command *command)
{
	int	i;
	
	i = 0;
	while (command->envp[i])
	{
		ft_putstr_fd(command->envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}