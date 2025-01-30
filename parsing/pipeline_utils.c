#include "../include/minishell.h"

t_pipeline	*free_pipeline_on_pipe_failure(t_pipeline *pipeline,
		size_t *i)
{
	while (*i > 0)
		free(pipeline->commands[*i--]);
	free(pipeline->commands);
	return (free(pipeline), NULL);
}
