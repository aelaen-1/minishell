/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:53:20 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 09:53:23 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_permission(char *cmd, t_context *context, struct stat path_stat)
{
	if (S_ISREG(path_stat.st_mode) && access(cmd, X_OK) == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			context->last_cmd_status = 126;
			return (126);
		}
	}
	return (0);
}

void	update_command_status(size_t *i, int ret, t_context *context)
{
	*i += 1;
	context->last_cmd_status = ret;
}

void	update_status_out(int ret, t_context *context)
{
	if (!context->last_cmd_status)
		context->last_cmd_status = ret;
}
