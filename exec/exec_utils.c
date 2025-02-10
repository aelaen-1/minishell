/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:19:36 by glabaden          #+#    #+#             */
/*   Updated: 2025/02/10 08:19:39 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path(t_command *cmd, t_env_node *envp)
{
	char	**full_path;
	size_t	i;
	char	*path_1;
	char	*path_to_try;
	char	*path_env_value;

	i = 0;
	if (access(cmd->argv[0], F_OK | X_OK) == 0)
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
			return (free(path_env_value), free(path_1),
				free_split(full_path), path_to_try);
		free(path_1);
		free(path_to_try);
		i++;
	}
	return (free(path_env_value), free_split(full_path), NULL);
}

int	return_exec(int ret_exec, t_program *program, t_context *context, int *pids)
{
	if (ret_exec == 421)
	{
		free(pids);
		free_program(program);
		free_env_node(context->envp);
		exit(context->last_cmd_status);
	}
	return (free(pids), -1);
}

void	wait_children(int *pids, t_context *context, t_program *p)
{
	int		status;
	size_t	i;

	status = 0;
	i = 0;
	while (i < p->pipeline->cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			context->last_cmd_status = WEXITSTATUS(status);
		i++;
	}
}
