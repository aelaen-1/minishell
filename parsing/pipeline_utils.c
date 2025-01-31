/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:16:20 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 10:16:21 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipeline	*free_pipeline_on_pipe_failure(t_pipeline *pipeline,
		size_t *i)
{
	while (*i > 0)
		free(pipeline->commands[*i--]);
	free(pipeline->commands);
	return (free(pipeline), NULL);
}
