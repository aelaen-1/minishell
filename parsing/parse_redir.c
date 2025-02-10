/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:15:58 by glabaden          #+#    #+#             */
/*   Updated: 2025/02/10 13:51:02 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	redir_out(t_command *cmd, t_token **current, t_token **last_token,
		t_token_type token_type)
{
	if (last_token - current < 2)
		return (-1);
	current++;
	if (!current || !*current || !(*current)->value
		|| (*current)->type != TOKEN_WORD)
		return (-1);
	if (cmd->redir_out.file)
		free(cmd->redir_out.file);
	cmd->redir_out.file = ft_strdup((*current)->value);
	if (token_type == TOKEN_REDIR_OUT)
		cmd->redir_out.type = REDIR_OUT;
	else if (token_type == TOKEN_APPEND)
		cmd->redir_out.type = REDIR_APPEND;
	return (1);
}

static int	redir_in(t_command *cmd, t_token **current, t_token **last_token)
{
	if (last_token - current < 2)
		return (-1);
	current++;
	if (!current || !*current || !(*current)->value
		|| (*current)->type != TOKEN_WORD)
		return (-1);
	if (cmd->redir_in.file)
		free(cmd->redir_in.file);
	cmd->redir_in.file = ft_strdup((*current)->value);
	cmd->redir_in.type = REDIR_IN;
	return (1);
}

static int	redir_heredoc(t_command *cmd, t_token **current, t_token **last_token, t_token **cmd_start)
{
	int		flag;

	flag = 1;
	if (last_token - current < 2)
		return (-1);
	if (current == cmd_start)
		flag = 2;
	current++;
	if (!current || !*current || !(*current)->value
		|| (*current)->type != TOKEN_WORD)
		return (-1);
	if (cmd->redir_in.file)
		free(cmd->redir_in.file);
	cmd->redir_in.file = ft_strdup((*current)->value);
	cmd->redir_in.type = REDIR_HEREDOC;
	return (flag);
}

int	parse_redir(t_command *cmd, t_token **current, t_token **last_token, t_token **cmd_start)
{
	if ((*current)->type == TOKEN_REDIR_OUT)
		return (redir_out(cmd, current, last_token, TOKEN_REDIR_OUT));
	else if ((*current)->type == TOKEN_APPEND)
		return (redir_out(cmd, current, last_token, TOKEN_APPEND));
	else if ((*current)->type == TOKEN_REDIR_IN)
		return (redir_in(cmd, current, last_token));
	else if ((*current)->type == TOKEN_HEREDOC)
		return (redir_heredoc(cmd, current, last_token, cmd_start));
	return (0);
}
