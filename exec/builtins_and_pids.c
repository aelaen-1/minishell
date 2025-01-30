#include "../include/minishell.h"

int	handle_builtin_commands(t_command *cmd, t_context *context)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (builtin_echo(cmd));
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (builtin_env(cmd, context));
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (builtin_pwd(cmd));
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		return (builtin_cd(cmd, context));
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (builtin_export(cmd, context));
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (builtin_unset(cmd, context));
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (builtin_exit(cmd, context));
	return (1);
}

int	is_builtin(t_command *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_command *cmd, t_context *context)
{
	int	buffer;

	close_command_fds(cmd);
	buffer = handle_builtin_commands(cmd, context);
	if (buffer != 421)
	{
		context->last_cmd_status = buffer;
		return (1);
	}
	return (421);
}

int	*malloc_pids(t_pipeline *pipeline)
{
	int		*pids;
	size_t	i;

	i = 0;
	pids = malloc(sizeof(int) * (pipeline->cmd_count + 1));
	if (!pids)
	{
		fprintf(stderr, "pids malloc error\n");
		return (0);
	}
	while (i < pipeline->cmd_count)
	{
		pids[i] = -1;
		i++;
	}
	pids[i] = 0;
	return (pids);
}
