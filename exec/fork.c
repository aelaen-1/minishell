/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:53:42 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 09:53:44 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int	fork_error(char **env, char *path)
{
	ft_putstr_fd("Fork error\n", 2);
	free_split(env);
	free(path);
	return (-1);
}

static void	close_pipe_fds(t_command *cmd)
{
	size_t	i;

	i = 0;
	while (i < cmd->pipeline->cmd_count)
	{
		if (i != cmd->index)
		{
			if (cmd->pipeline->commands[i]->fds[0] != -1
				&& cmd->pipeline->commands[i]->fds[0] != 0)
				close(cmd->pipeline->commands[i]->fds[0]);
			if (cmd->pipeline->commands[i]->fds[1] != -1
				&& cmd->pipeline->commands[i]->fds[1] != 1)
				close(cmd->pipeline->commands[i]->fds[1]);
		}
		i++;
	}
}

static int	child_process(t_command *cmd, char *path, char **env)
{
	int	res;

	res = 0;
	close_pipe_fds(cmd);
	dup2(cmd->fds[0], 0);
	dup2(cmd->fds[1], 1);
	close_command_fds(cmd);
	res = execve(path, cmd->argv, env);
	return (res);
}

int	do_fork(t_command *cmd, int *pid, char *path, t_context *context)
{
	char	**env;
	int		res;

	res = 0;
	env = lst_to_char(context->envp);
	*pid = fork();
	if (*pid == -1)
		return (fork_error(env, path));
	if (*pid == 0)
		res = child_process(cmd, path, env);
	else
		close_command_fds(cmd);
	free_split(env);
	return (res);
}
