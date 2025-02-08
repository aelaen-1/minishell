/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:51:32 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 09:51:34 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validate_exit_argument(char *arg)
{
	int	i;
	int	status;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && arg[i] != '-' && arg[i] != '+')
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (2);
		}
		i++;
	}
	status = ft_atoi(arg);
	return (status);
}

int	builtin_exit(t_command *command, t_context *context)
{
	int	status;
	size_t	flag;

	flag = command->pipeline->cmd_count;
	status = 0;
	if (!command->argv[1] && flag == 1)
		return (ft_putstr_fd("exit\n", command->fds[1]), 421);
	if (command->argv[1] && command->argv[2])
	{
		ft_putstr_fd("exit\n", command->fds[1]);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (command->argv[1])
		status = validate_exit_argument(command->argv[1]);
	context->last_cmd_status = status;
	if (flag == 1)
	{
		ft_putstr_fd("exit\n", command->fds[1]);
		return (421);
	}
	return (status);
}
