/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:51:24 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 09:51:26 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_env(t_command *command, t_context *context)
{
	t_env_node	*loop;

	if (!command || !context->envp)
		return (0);
	loop = context->envp;
	while (loop)
	{
		if (ft_strchr(loop->env_var, '='))
		{
			ft_putstr_fd(loop->env_var, command->fds[1]);
			ft_putchar_fd('\n', command->fds[1]);
			loop = loop->next;
		}
		else
			loop = loop->next;
	}
	return (0);
}
