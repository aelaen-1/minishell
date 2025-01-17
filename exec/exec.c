#include "../include/minishell.h"

static char	*get_path(t_command *cmd, t_program *program)
{
	char	**full_path;
	size_t	i;
	char	*path_1;
	char	*path_to_try;

	i = 0;
	full_path = ft_split(get_env_value("PATH", program), ':');
	while (full_path[i])
	{
		path_1 = ft_strjoin(full_path[i], "/");
		path_to_try = ft_strjoin(path_1, cmd->argv[0]);
		if (access(path_to_try, F_OK | X_OK) == 0)
		{
			free(path_1);
			return (path_to_try);
		}
		free(path_1);
		free(path_to_try);
		i++;
	}
	if (!full_path[i])
		ft_putstr_fd("Path not found\n", 2);
	return (NULL);
}

int	handle_builtin_commands(t_command *cmd, t_program *program)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (builtin_echo(cmd));
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (builtin_env(cmd, program));
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (builtin_pwd());
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		return (builtin_cd(cmd, program));
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (builtin_export(cmd, program));
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (builtin_unset(cmd, program));
	return (1);
}

int	handle_redirection(t_command *cmd)
{
	int	fd;

	if (cmd->redir_in.type == REDIR_IN)
	{
		fd = open(cmd->redir_in.file, O_RDONLY);
		if (fd == -1)
			return (ft_putstr_fd("Infile not found\n", 2), -1);
		dup2(fd, 0);
	}
	if (cmd->redir_out.type == REDIR_OUT)
	{
		fd = open(cmd->redir_out.file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (ft_putstr_fd("Outfile not found\n", 2), -1);
		dup2(fd, 1);
	}
	else if (cmd->redir_out.type == REDIR_APPEND)
	{
		fd = open(cmd->redir_out.file, O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			return (ft_putstr_fd("Outfile not found\n", 2), -1);
		dup2(fd, 1);
	}
	return (0);
}

int	exec_cmd(t_command *cmd, t_program *program)
{
	char	*path;

	if (!handle_builtin_commands(cmd, program))
		return (0);
	path = get_path(cmd, program);
	if (!path)
		return (-1);
	if (handle_redirection(cmd) == -1)
		return (-1);
	if (execve(path, cmd->argv, NULL) == -1)
	{
		ft_putstr_fd("Could not execute following cmd: ", 2);
		ft_putendl_fd(cmd->argv[0], 2);
		exit(1);
	}
	return (0);
}
