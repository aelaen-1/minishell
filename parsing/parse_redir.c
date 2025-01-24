#include "../include/minishell.h"

// ATTENTION SI PLUSEURS REDIRECTIONS 
// si on a strdup un token et que le token suivant 
// n'est pas un WORD, on free le strdup et on return -1
//DANS DESTROY COMMAND()
static int	redir_out(t_command *cmd, t_token ***current,
		t_token_type token_type)
{
	(*current)++;
	if (!(*current) || !(**current) || !(**current)->value)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return	(-1);
	}
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
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return	(-1);
	}
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
		return (redir_out(cmd, &current, TOKEN_REDIR_OUT));
	else if ((*current)->type == TOKEN_APPEND)
		return (redir_out(cmd, &current, TOKEN_APPEND));
	else if ((*current)->type == TOKEN_REDIR_IN)
		return (redir_in(cmd, &current, TOKEN_REDIR_IN));
	else if ((*current)->type == TOKEN_HEREDOC)
		return (redir_in(cmd, &current, TOKEN_HEREDOC));
	return (0);
}
