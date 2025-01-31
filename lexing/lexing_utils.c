/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:14:17 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 10:14:23 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_quote(char c)
{
	if (c == SIMPLE_QUOTE || c == DOUBLE_QUOTE)
		return (1);
	return (0);
}

int	is_pipe_or_redir(char c)
{
	if (c == PIPE || c == LESS || c == GREAT)
		return (1);
	return (0);
}

int	is_double_redir(char c, char d)
{
	if ((c == LESS && d == LESS) || (c == GREAT && d == GREAT))
		return (1);
	return (0);
}
