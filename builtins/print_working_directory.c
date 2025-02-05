/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_directory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:51:58 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 09:52:00 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_pwd(t_command *command)
{
	char	*working_directory;

	working_directory = getcwd(NULL, 0);
	ft_putstr_fd(working_directory, command->fds[1]);
	ft_putchar_fd('\n', command->fds[1]);
	free(working_directory);
	return (0);
}
