/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:17:09 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 10:17:11 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig = 0;

void	ctrlc_exit_status(t_context *context)
{
	context->last_cmd_status = 130;
	g_sig = 0;
}

void	handle_ctrlc(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig = sig + 128;
}

void	handle_ctrlc_exec(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	g_sig = sig + 128;
}

void	handle_ctrlc_heredoc(int sig)
{
	write(1, "\n", 1);
	g_sig = sig + 128;
}
void	handle_sig_quit(int sig)
{
	write(2, "Quit (core dumped)\n", 19);
	g_sig = sig + 128;
}

void	signal_handler(void)
{
	signal(SIGINT, handle_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}
