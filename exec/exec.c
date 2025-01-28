#include "../include/minishell.h"


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

static char	*get_path(t_command *cmd, t_env_node *envp, int	*should_free_path)
{
	char	**full_path;
	size_t	i;
	char	*path_1;
	char	*path_to_try;
	char	*path_env_value;


	i = 0;
	if(access(cmd->argv[0], F_OK | X_OK) == 0)
	{
		*should_free_path = 0;
		return (cmd->argv[0]);
	}
	path_env_value = get_env_value("PATH", envp);
	if (!path_env_value)
		return (ft_putstr_fd("minishell: PATH not set\n", STDERR_FILENO), NULL);
	full_path = ft_split(path_env_value, ':');
	while (full_path[i])
	{
		path_1 = ft_strjoin(full_path[i], "/");
		path_to_try = ft_strjoin(path_1, cmd->argv[0]);
		if (access(path_to_try, F_OK | X_OK) == 0)
		{
			free(path_env_value);
			free(path_1);
			free_split(full_path);
			return (path_to_try);
		}
		
		free(path_1);
		free(path_to_try);
		i++;
	}
	return (free(path_env_value), free_split(full_path), NULL);
}

static int  exec_cmd(t_command *cmd, int *pid, t_context *context)
{
	int should_free_path;
	char *path;
	char **env;
	
	env = NULL;
	should_free_path = 1;
    if (!cmd || !cmd->argv[0])
        return (0);
    expand_command(cmd, context);
	if (!redirect_command(cmd))
		return (0);
    if (is_builtin(cmd))
	{
        return (handle_builtin_commands(cmd, context), close_command_fds(cmd), 0);
	}
	path = get_path(cmd, context->envp, &should_free_path);
	context->last_cmd_status = handle_exec_error(path, context);
	if (context->last_cmd_status)
		return (context->last_cmd_status);
	env = lst_to_char(context->envp);
    *pid = fork();
    if (*pid == 0)
    {
        dup2(cmd->fds[0], 0);
        dup2(cmd->fds[1], 1);
        close_command_fds(cmd);
        if (execve(path, cmd->argv, env) == -1)
		{
			if (should_free_path == 1)
				free(path);
			return (free_split(env), -1);
		}
    }
	else
		close_command_fds(cmd);
	free_split(env);
	if (should_free_path == 1)
		free(path);
	return (0);
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
	free(pids);
	return (0);
}
