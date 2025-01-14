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
	t_env_node	*loop;
	
	if(!command || !command->envp)
		return 0;
	
	loop = command->envp;
	while (loop)
	{
		ft_putstr_fd(loop->env_var, 1);
		ft_putchar_fd('\n', 1);
		loop = loop->next;
	}
	return (0);
}