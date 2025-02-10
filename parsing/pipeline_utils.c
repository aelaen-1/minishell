/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:16:20 by glabaden          #+#    #+#             */
/*   Updated: 2025/02/10 13:55:43 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipeline	*free_pipeline_on_pipe_failure(t_pipeline *pipeline,
		size_t *i, t_context *context)
{
	size_t	j;

	j = 0;
	context->last_cmd_status = 2;
	while (j <= *i)
	{
		destroy_command(pipeline->commands[j]);
		j++;
	}
	free(pipeline->commands);
	return (free(pipeline), NULL);
}

void	close_command_fds(t_command *command)
{
	if (command->fds[0] != 0 && command->fds[0] != -1)
	{
		close(command->fds[0]);
		command->fds[0] = -1;
	}
	if (command->fds[1] != 1 && command->fds[1] != -1)
	{
		close(command->fds[1]);
		command->fds[1] = -1;
	}
}
