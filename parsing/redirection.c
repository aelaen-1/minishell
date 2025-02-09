/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:18:00 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 10:18:02 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_sig;

static int	redir_in_message(t_command *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command->redir_in.file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (0);
}

static int	redir_out_message(t_command *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command->redir_out.file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (0);
}

int	redirect_command(t_command *command)
{
	if (command->redir_in.file && command->redir_in.type == REDIR_IN)
	{
		command->fds[0] = open(command->redir_in.file, O_RDONLY);
		if (command->fds[0] == -1)
			return (redir_in_message(command));
	}
	if (command->redir_in.file && command->redir_in.type == REDIR_HEREDOC)
	{
		if (handle_heredoc(command))
			return (0);
	}
	if (command->redir_out.file && command->redir_out.type == REDIR_OUT)
	{
		command->fds[1] = open(command->redir_out.file, O_RDWR | O_CREAT
				| O_TRUNC, 0777);
		if (command->fds[1] == -1)
			return (redir_out_message(command));
	}
	if (command->redir_out.file && command->redir_out.type == REDIR_APPEND)
	{
		command->fds[1] = open(command->redir_out.file, O_RDWR | O_CREAT
				| O_APPEND, 0777);
		if (command->fds[1] == -1)
			return (redir_out_message(command));
	}
	return (1);
}