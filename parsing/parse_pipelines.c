#include "../include/minishell.h"

static size_t	count_pipes(t_token **start, t_token **end)
{
	size_t	i;

	i = 0;
	while (start < end)
	{
		if ((*start)->type == TOKEN_PIPE)
			i++;
		start++;
	}
	return (i);
}

static t_token	**find_token(t_token **start, t_token **end,
		t_token_type token_type)
{
	while (start < end)
	{
		if ((*start)->type == token_type)
			return (start);
		start++;
	}
	return (end);
}

static int	check_if_pipeline_error(t_token **start, t_token **end,
		size_t cmd_count)
{
	t_token	**command_end;

	while (start < end && cmd_count > 0)
	{
		command_end = find_token(start, end, TOKEN_PIPE);
		if (command_end == start)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
			ft_putstr_fd("`|'\n", 2);
			return (1);
		}
		start = command_end + 1;
	}
	if (start == end)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

static t_pipeline	*free_pipeline_on_pipe_failure(t_pipeline *pipeline,
		size_t *i)
{
	while (*i > 0)
		free(pipeline->commands[*i--]);
	free(pipeline->commands);
	return (free(pipeline), NULL);
}

t_pipeline	*parse_pipeline(t_token **start, t_token **end)
{
	t_pipeline	*pipeline;
	size_t		i;
	t_token		**command_end;

	i = 0;
	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->cmd_count = count_pipes(start, end) + 1;
	pipeline->commands = malloc(sizeof(t_command *) * pipeline->cmd_count);
	if (!pipeline->commands)
		return (free(pipeline), NULL);
	if (check_if_pipeline_error(start, end, pipeline->cmd_count))
		return (free(pipeline->commands), free(pipeline), NULL);
	while (start < end && i < pipeline->cmd_count)
	{
		command_end = find_token(start, end, TOKEN_PIPE);
		if (command_end == start)
			return (free_pipeline_on_pipe_failure(pipeline, &i));
		pipeline->commands[i] = parse_command(start, command_end);
		if (!pipeline->commands[i])
			return (free_pipeline_on_pipe_failure(pipeline, &i));
		start = command_end + 1;
		i++;
	}
	return (pipeline);
}
