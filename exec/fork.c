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

static int	child_process(t_command *cmd, char *path, char **env)
{
	int	res;

	res = 0;
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
