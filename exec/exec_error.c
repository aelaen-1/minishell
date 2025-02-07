/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:53:33 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 09:53:35 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int		g_sig;

static int	is_directory(char *cmd, t_context *context, struct stat path_stat)
{
	if (S_ISDIR(path_stat.st_mode))
	{
		if (cmd[0] == '.' || cmd[0] == '/')
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			context->last_cmd_status = 126;
			g_sig = 1;
			return (126);
		}
		else
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			context->last_cmd_status = 127;
			g_sig = 1;
			return (127);
		}
	}
	return (0);
}

static int	permission_denied(char *cmd, t_context *context)
{
	if (access(cmd, F_OK) == 0 && access(cmd, R_OK) == -1
		&& access(cmd, W_OK) == -1 && access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		context->last_cmd_status = 126;
		g_sig = 1;
		return (126);
	}
	else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		context->last_cmd_status = 127;
		g_sig = 1;
		return (127);
	}
	return (0);
}

static int	exec_error_on_filedir(char *cmd, t_context *context, struct stat ps)
{
	int	res;

	res = permission_denied(cmd, context);
	if (res)
		return (res);
	res = is_directory(cmd, context, ps);
	if (res)
		return (res);
	res = exec_permission(cmd, context, ps);
	if (res)
		return (res);
	return (0);
}

static int	exec_error_otherwise(char *cmd, t_context *context)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		if (cmd[0] == '.' || cmd[0] == '/')
		{
			ft_putstr_fd(": No such file or directory\n", 2);
			context->last_cmd_status = 127;
		}
		else
		{
			ft_putstr_fd(": command not found\n", 2);
			context->last_cmd_status = 1;
		}
		g_sig = 1;
		return (context->last_cmd_status);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	context->last_cmd_status = 127;
	g_sig = 1;
	return (context->last_cmd_status);
}

int	handle_exec_error(char *cmd, t_context *context)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == 0)
		return (exec_error_on_filedir(cmd, context, path_stat));
	else
		return (exec_error_otherwise(cmd, context));
}
