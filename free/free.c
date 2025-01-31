/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:06:28 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 10:06:30 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_command_argv(char **cmd_arg)
{
	int	i;

	i = 0;
	if (cmd_arg)
	{
		while (cmd_arg[i])
		{
			free(cmd_arg[i]);
			i++;
		}
		free(cmd_arg);
		cmd_arg = NULL;
	}
}

void	free_env_node(t_env_node *node)
{
	t_env_node	*temp;

	while (node)
	{
		temp = node->next;
		free(node->env_var);
		free(node);
		node = temp;
	}
}

void	free_pipeline(t_pipeline *pipeline)
{
	size_t	i;

	i = 0;
	if (!pipeline)
		return ;
	while (pipeline->cmd_count != i)
	{
		if (pipeline->commands[i])
			destroy_command(pipeline->commands[i]);
		i++;
	}
	free(pipeline->commands);
	free(pipeline);
}

void	free_program(t_program *program)
{
	free_pipeline(program->pipeline);
	free(program);
}
