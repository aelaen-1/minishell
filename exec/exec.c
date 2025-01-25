#include "../include/minishell.h"

void command_not_found_and_free(char *arg, char *path, char **env, int *should_free_path)
{
    if (path != NULL && *should_free_path == 1)
		free(path);
	free_split(env); // ne fait rien si env est NULL
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(": command not found\n", 2);
}

static void	link_pipeline(t_pipeline *pipeline)
{
	size_t	i;
	int	pipe_fds[2];

	i = 0;
	while (i < pipeline->cmd_count - 1)
	{
		pipe(pipe_fds);
		pipeline->commands[i]->fds[1] = pipe_fds[1];
		// if (pipeline->commands[i + 1]) condition inutile car on sait qu'il y a un élément suivant (i < pipeline->cmd_count - 1)
		pipeline->commands[i+1]->fds[0] = pipe_fds[0];
		i++;
	}
}

//met la valeur de free_path à 0 si on peut accéder à cmd->argv[0]
static char	*get_path(t_command *cmd, t_env_node *envp, int	*should_free_path)
{
	char	**full_path;
	size_t	i;
	char	*path_1;
	char	*path_to_try;
	char	*path_env_value;


	i = 0;
	path_env_value = get_env_value("PATH", envp);
	if(access(cmd->argv[0], F_OK | X_OK) == 0)
	{
		*should_free_path = 0;
		return (cmd->argv[0]);
	}
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
        return (-1);
    expand_command(cmd, context);
    redirect_command(cmd);
    if (is_builtin(cmd))
    {
        handle_builtin_commands(cmd, context);
        close_command_fds(cmd);
        return (0);
    }
    *pid = fork();
    if (*pid == 0)
    {
        dup2(cmd->fds[0], 0);
        dup2(cmd->fds[1], 1);
        close_command_fds(cmd);
		path = get_path(cmd, context->envp, &should_free_path);
		if (!path)
		{
			context->last_cmd_status = 127;
			return (command_not_found_and_free(cmd->argv[0], path, env, &should_free_path), -1);
		}
		env = lst_to_char(context->envp);
        if (execve(path, cmd->argv, env) == -1)
		{
			context->last_cmd_status = 127;
			return (command_not_found_and_free(cmd->argv[0], path, env, &should_free_path), -1);
		}
    }
	else
		close_command_fds(cmd);
	return (0);
}

void	execute_program(t_program *program, t_context *context)
{
	size_t	i;
	int *pids;
	int status;

	i = 0;
	pids = malloc_pids(program->pipeline);
	link_pipeline(program->pipeline);
	while (i < program->pipeline->cmd_count)
	{
		if (exec_cmd(program->pipeline->commands[i], &pids[i], context) == -1)
			break ;
		i++;
	}
	i = 0;
	while (i < program->pipeline->cmd_count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
        context->last_cmd_status = WEXITSTATUS(status);
	free(pids);
}

