/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:18:40 by glabaden          #+#    #+#             */
/*   Updated: 2025/02/10 08:18:44 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_sig;

static void	handle_ctrlc_heredoc(int sig)
{
	g_sig = 128 + sig;
	write(1, "\n", 1);
	close(0);
}

static void	write_heredoc_to_pipe(int *pipe_fd1, char *line)
{
	ft_putstr_fd(line, *pipe_fd1);
	ft_putchar_fd('\n', *pipe_fd1);
	free(line);
}

int	handle_heredoc(t_command *command)
{
	int		pipe_fds[2];
	char	*line;
	int		stdin_dup;

	pipe(pipe_fds);
	command->fds[0] = pipe_fds[0];
	stdin_dup = dup(STDIN_FILENO);
	signal(SIGINT, handle_ctrlc_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("heredoc> ");
		if (g_sig == 130 || !line || !ft_strcmp(line, command->redir_in.file))
		{
			free(line);
			break ;
		}
		write_heredoc_to_pipe(&pipe_fds[1], line);
	}
	close(pipe_fds[1]);
	if (g_sig != 130)
		return (close(stdin_dup), 0);
	else
		return (close(command->fds[0]), dup2(stdin_dup, 0),
			close(stdin_dup), 1);
}
