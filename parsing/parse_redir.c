#include "../include/minishell.h"

// returns 1 if the redir op is followed by a TOKEN_WORD
static int	redir_out(t_command *cmd, t_token ***current,
		t_token_type token_type)
{
	(*current)++;
	if (!(*current) || !(**current) || !(**current)->value)
		return (0);
	if ((**current)->type == TOKEN_WORD)
	{
		cmd->redir_out.file = ft_strdup((**current)->value);
		if (token_type == TOKEN_REDIR_OUT)
			cmd->redir_out.type = REDIR_OUT;
		else if (token_type == TOKEN_APPEND)
			cmd->redir_out.type = REDIR_APPEND;
		return (1);
	}
	return (0);
}

static int	redir_in(t_command *cmd, t_token ***current, t_token_type token_type)
{
	(*current)++;
	if (!(*current) || !(**current) || !(**current)->value)
		return (0);
	if ((**current)->type == TOKEN_WORD)
	{
		cmd->redir_in.file = ft_strdup((**current)->value);
		if (token_type == TOKEN_REDIR_IN)
			cmd->redir_in.type = REDIR_IN;
		else if (token_type == TOKEN_HEREDOC)
			cmd->redir_in.type = REDIR_HEREDOC;
		return (1);
	}
	return (0);
}

int	parse_redir(t_command *cmd, t_token **current)
{
	if ((*current)->type == TOKEN_REDIR_OUT)
	{
		if (redir_out(cmd, &current, TOKEN_REDIR_OUT))
			return (1);
	}
	else if ((*current)->type == TOKEN_APPEND)
	{
		if (redir_out(cmd, &current, TOKEN_APPEND))
			return (1);
	}
	else if ((*current)->type == TOKEN_REDIR_IN)
	{
		if (redir_in(cmd, &current, TOKEN_REDIR_IN))
			return (1);
	}
	else if ((*current)->type == TOKEN_HEREDOC)
	{
		if (redir_in(cmd, &current, TOKEN_HEREDOC))
			return (1);
	}
	return (0);
}
