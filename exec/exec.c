#include "../include/minishell.h"

extern int		g_sig;

static void	link_pipeline(t_pipeline *pipeline)
{
	size_t	i;
	int	pipe_fds[2];

	i = 0;
	while (i < pipeline->cmd_count - 1)
	{
		pipe(pipe_fds);
		pipeline->commands[i]->fds[1] = pipe_fds[1];
		pipeline->commands[i + 1]->fds[0] = pipe_fds[0];
		i++;
	}
}

static char	*get_path(t_command *cmd, t_env_node *envp)
{
	char	**full_path;
	size_t	i;
	char	*path_1;
	char	*path_to_try;
	char	*path_env_value;


	i = 0;
	if(access(cmd->argv[0], F_OK | X_OK) == 0)
		return (ft_strdup(cmd->argv[0]));
	path_env_value = get_env_value("PATH", envp);
	if (!path_env_value)
		return (ft_putstr_fd("minishell: PATH not set\n", 2), NULL);
	full_path = ft_split(path_env_value, ':');
	while (full_path[i])
	{
		path_1 = ft_strjoin(full_path[i], "/");
		path_to_try = ft_strjoin(path_1, cmd->argv[0]);
		if (access(path_to_try, F_OK | X_OK) == 0)
			return (free(path_env_value), free(path_1), free_split(full_path), path_to_try);
		free(path_1);
		free(path_to_try);
		i++;
	}
	return (free(path_env_value), free_split(full_path), NULL);
}

static int  exec_cmd(t_command *cmd, int *pid, t_context *context)
{
	char *path;
	int	res;
	
	res = 0;
    if (!cmd || !cmd->argv[0])
        return (0);
    expand_command(cmd, context);
	if (!cmd->argv[0])
		return (56);
	if (!redirect_command(cmd))
		return (0);
    if (is_builtin(cmd))
		return (exec_builtin(cmd, context));
	path = get_path(cmd, context->envp);
	context->last_cmd_status = handle_exec_error(path ? path : cmd->argv[0], context);
	if (context->last_cmd_status)
		return (free(path), context->last_cmd_status);
	res = do_fork(cmd, pid, path, context);
	return (free(path), res);
}

int	execute_program(t_program *program, t_context *context)
{
	size_t	i;
	int *pids;
	int status;

	i = 0;
	status = 0;
	pids = malloc_pids(program->pipeline);
	link_pipeline(program->pipeline);
	g_sig = 2;
	while (i < program->pipeline->cmd_count)
	{
		if (exec_cmd(program->pipeline->commands[i], &pids[i], context))
			return (free(pids), -1);
		else
			i++;
	}
	i = 0;
	while (i < program->pipeline->cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			context->last_cmd_status = WEXITSTATUS(status);
		i++;
	}
	return (g_sig = 0, free(pids), 0);
}
