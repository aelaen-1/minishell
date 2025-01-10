/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_directory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvastel <lvastel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:18:13 by lvastel           #+#    #+#             */
/*   Updated: 2024/12/13 16:52:15 by lvastel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_pwd()
{
	char *working_directory;

    working_directory = getenv("PWD");
    ft_putstr_fd(working_directory, 1);
    ft_putchar_fd('\n', 1);

	return (0);
}