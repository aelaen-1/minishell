/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:35:46 by lvastel           #+#    #+#             */
/*   Updated: 2025/01/23 23:58:28 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void handle_ctrlc()
{
    write(1, "\n",1);
    rl_replace_line("",0);
    rl_on_new_line();
    rl_redisplay();
}
void handle_ctrlslash()
{
    rl_replace_line(" ",1);
}
void signal_handler()
{
    signal(SIGINT,  handle_ctrlc);
    signal(SIGQUIT, handle_ctrlslash);
}


