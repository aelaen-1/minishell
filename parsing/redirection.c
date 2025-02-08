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

void	handle_ctrlc_heredoc(int sig)
{
	g_sig = 128 + sig;
	write(1, "\n", 1);
	close(0);
}

static int	handle_heredoc(t_command *command)
{
	int		pipe_fds[2];
	char	*line;
	int		stdin_dup;

	pipe(pipe_fds);
	command->fds[0] = pipe_fds[0];
	stdin_dup = dup(STDIN_FILENO);
	signal(SIGINT, handle_ctrlc_heredoc);
	while (1)
	{
		line = readline("heredoc> ");
		if(g_sig == 130 || !line || !ft_strcmp(line, command->redir_in.file))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fds[1]);
		ft_putchar_fd('\n', pipe_fds[1]);
		free(line);
	}
	close(pipe_fds[1]);
	if (g_sig != 130)
	{
		close(stdin_dup);
		return (0);
	}
	else
	{
		close(command->fds[0]);
		dup2(stdin_dup, 0);
		close(stdin_dup);
		return (1);
	}
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