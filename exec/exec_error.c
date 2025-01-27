#include "../include/minishell.h"

static int is_directory(char *cmd, t_context *context, struct stat path_stat)
{
	if (S_ISDIR(path_stat.st_mode))
	{
		if (cmd[0] == '.' || cmd[0] == '/')
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			context->last_cmd_status = 126;
			return (126);
		}
		else
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			context->last_cmd_status = 127;
			return (127);
		}
	}
	return (0);
}
static int permission_denied(char *cmd, t_context *context)
{
	if (access(cmd, F_OK) == 0 && access(cmd, R_OK) == -1
		&& access(cmd, W_OK) == -1 && access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		context->last_cmd_status = 126;
		return (126);
	}
	else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		context->last_cmd_status = 127;
		return (127);
	}
	return (0);
}
static int exec_permission(char *cmd, t_context *context, struct stat path_stat)
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

static	int exec_error_on_filedir(char *cmd, t_context	*context, struct stat path_stat)
{
	int	res;

	res = is_directory(cmd, context, path_stat);
	if (res)
		return (res);
	res = permission_denied(cmd, context);
	if (res)
		return (res);
	res = exec_permission(cmd, context, path_stat);
	if (res)
		return (res);
	return (0);
}
static int exec_error_otherwise(char *cmd, t_context *context)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		if (cmd[0] == '.' || cmd[0] == '/')
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		context->last_cmd_status = 127;
		return (context->last_cmd_status);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	context->last_cmd_status = 127;
	return (context->last_cmd_status);
}

int	handle_exec_error(char *cmd, t_context *context)
{
	struct stat path_stat;

	
	if (stat(cmd, &path_stat) == 0)
		return (exec_error_on_filedir(cmd, context, path_stat));
	else
		return (exec_error_otherwise(cmd, context));
}
