/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:53:11 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 09:53:12 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int		g_sig;

static void	link_pipeline(t_pipeline *pipeline)
{
	size_t	i;
	int		pipe_fds[2];

	i = 0;
	while (i < pipeline->cmd_count - 1)
	{
		pipe(pipe_fds);
		pipeline->commands[i]->fds[1] = pipe_fds[1];
		pipeline->commands[i + 1]->fds[0] = pipe_fds[0];
		i++;
	}
	signal(SIGINT, handle_ctrlc_exec);
	signal(SIGQUIT, handle_sig_quit);
}

static int	exec_cmd(t_command *cmd, int *pid, t_context *context)
{
	char	*path;
	int		res;

	res = 0;
	if (!cmd || !cmd->argv[0])
		return (0);
	expand_command(cmd, context);
	if (!cmd->argv[0])
		return (0);
	if (!redirect_command(cmd))
		return (1);
	if (is_builtin(cmd))
		return (exec_builtin(cmd, context));
	path = get_path(cmd, context->envp);
	if (!path)
		context->last_cmd_status = handle_exec_error(cmd->argv[0], context);
	else
		context->last_cmd_status = handle_exec_error(path, context);
	if (context->last_cmd_status)
		return (free(path), context->last_cmd_status);
	res = do_fork(cmd, pid, path, context);
	return (free(path), res);
}

int	execute_program(t_program *program, t_context *context)
{
	size_t	i;
	int		*pids;
	int		ret_exec;

	i = 0;
	pids = malloc_pids(program->pipeline);
	link_pipeline(program->pipeline);
	while (i < program->pipeline->cmd_count)
	{
		ret_exec = exec_cmd(program->pipeline->commands[i], &pids[i], context);
		if (ret_exec == 421)
			return (return_exec(ret_exec, program, context, pids));
		else if (ret_exec)
		{
			context->last_cmd_status = ret_exec;
			break ;
		}
		update_command_status(&i, ret_exec, context);
	}
	wait_children(pids, context, program);
	update_status_out(ret_exec, context);
	return (free(pids), 0);
}
