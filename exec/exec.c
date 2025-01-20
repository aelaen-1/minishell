#include "../include/minishell.h"

static int	handle_builtin_commands(t_command *cmd, t_expansion_context *context)
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
        {
            close(cmd->fds[0]);
        }
        if (cmd->fds[1] != 1)
        {
            close(cmd->fds[1]);
        }
}
static char	*get_path(t_command *cmd, t_env_node *envp)
{
	char	**full_path;
	size_t	i;
	char	*path_1;
	char	*path_to_try;

	i = 0;
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

static int exec_cmd(t_command *cmd, int *pid, t_expansion_context *context)
{
    char    *path;

	expand_command(cmd, context);
	redirect_command(cmd);
    if (!handle_builtin_commands(cmd, context))
    {
        close_command_fds(cmd);
        return (0);
    }
    path = get_path(cmd, context->envp);
    *pid = fork();
    if (*pid == 0)
    {
        dup2(cmd->fds[0], 0);
        dup2(cmd->fds[1], 1);
        close_command_fds(cmd);
        if (execve(path, cmd->argv, NULL) == -1)
        {
            fprintf(stderr, "minishell: %s: command not found\n", cmd->argv[0]);
            exit(1);
        }
    }
    else
    {
        close_command_fds(cmd);
    }
    return (0);
} 


void	execute_program(t_program *program, t_expansion_context *context)
{
	size_t	i;
	int *pids;

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
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
}




// 		 cat infile 			  | 		     wc                 |                grep 2
// fd[i-1][0]     	  fd[i-1][1]		   fd[i][1]     fd[i][0]              fd[i + 1][0]          fd[i + 1][1]

// first cmd :                       |          
// dup2(fd[0], 0);				     	if (redir_in.file == NULL)		|   if (redir_in file == NULL)
// if (redir_out.file)						dup2(fd[i-1][0], fd[i][1])			dup2(fd[i][0], dup2[fd[1]])
// 	dup2(fd[1], stdout);												


// void	link_commands_fds(t_pipeline *pipeline)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < pipeline->cmd_count)
// 	{
// 		pipe(pipeline->commands[i]->fds);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < pipeline->cmd_count)
// 	{
// 		if (i == 0) // 1ere commande
// 			i++;
// 		else
// 		{
// 			// stdin de notre commande est le stdout de la commande précédente si notre commande n'a pas d'infile
// 			// et la commande précédente n'a pas d'outfile
// 			if(pipeline->commands[i]->redir_in.file == NULL && pipeline->commands[i-1]->redir_out.file == NULL)
// 			{
// 				dup2(pipeline->commands[i-1]->fds[0], pipeline->commands[i]->fds[1]);
// 				i++;
// 			}
// 		}
// 	}
// 	// free_fds(fds, pipeline->cmd_count);
// }

