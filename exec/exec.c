#include "../include/minishell.h"

static int	handle_builtin_commands(t_command *cmd, t_context *context)
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
	return (1);
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
		pipeline->commands[i+1]->fds[0] = pipe_fds[0];

		i++;
	}
}

static void close_command_fds(t_command *cmd)
{
          if (cmd->fds[0] != 0)
            close(cmd->fds[0]);
        if (cmd->fds[1] != 1)
            close(cmd->fds[1]);
}
static char	*get_path(t_command *cmd, t_env_node *envp)
{
	char	**full_path;
	size_t	i;
	char	*path_1;
	char	*path_to_try;

	i = 0;
	if(access(cmd->argv[0], F_OK | X_OK) == 0)
		return cmd->argv[0];
	full_path = ft_split(get_env_value("PATH", envp), ':');
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
	return (NULL);
}
char **make_env_char(t_env_node *top)
{
    int count = 0;
    t_env_node *current = top;
    char **env_array;

    // Count the number of nodes in the linked list
    while (current)
    {
        count++;
        current = current->next;
    }

    // Allocate memory for the char ** array
    env_array = (char **)malloc((count + 1) * sizeof(char *));
    if (!env_array)
        return NULL;

    // Reset the current pointer and fill the array
    current = top;
    for (int i = 0; i < count; i++)
    {
        env_array[i] = strdup(current->env_var);
        if (!env_array[i])
        {
            // Free previously allocated memory on failure
            for (int j = 0; j < i; j++)
                free(env_array[j]);
            free(env_array);
            return NULL;
        }
        current = current->next;
    }

    // Null-terminate the array
    env_array[count] = NULL;

    return env_array;
}

static int exec_cmd(t_command *cmd, int *pid, t_context *context)
{
    if (!cmd || !cmd->argv[0])
        return 0;
    expand_command(cmd, context);
    redirect_command(cmd);

    // Builtins qui modifient l'env sans pipe
    if (*pid == -1 && (!ft_strcmp(cmd->argv[0], "export") || 
        !ft_strcmp(cmd->argv[0], "cd") || 
        !ft_strcmp(cmd->argv[0], "unset")))
    {
        if (!handle_builtin_commands(cmd, context))
        {
            close_command_fds(cmd);
            return (0);
        }
    }
    else
    {
        *pid = fork();
        if (*pid == 0)
        {
            dup2(cmd->fds[0], 0);
            dup2(cmd->fds[1], 1);
            close_command_fds(cmd);
            if (!handle_builtin_commands(cmd, context))
                exit(0);
            char **env = make_env_char(context->envp);
            char *path = get_path(cmd, context->envp);
            if (execve(path, cmd->argv, env) == -1)
            {
                fprintf(stderr, "minishell: %s: command not found\n", cmd->argv[0]);
                free(path);
                free_split(env);
                exit(1);
            }
        }
        close_command_fds(cmd);
    }
    return (1);
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
		exec_cmd(program->pipeline->commands[i], &pids[i], context);
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


