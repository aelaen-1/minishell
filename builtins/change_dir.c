/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvastel <lvastel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:15:30 by lvastel           #+#    #+#             */
/*   Updated: 2024/12/13 13:15:35 by lvastel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	builtin_cd(t_command *command)
{
	char *alternate_path;

	if (!command->argv[1])
	{
		alternate_path = getenv("HOME");
		ft_putstr_fd(alternate_path, 1);
		if (alternate_path == NULL)
            return (write(2, "cd: HOME not set\n", 17),-1);
	}
	else 
		alternate_path = command->argv[1];
	if (chdir(alternate_path) != 0) 
	{
        return (perror("cd"),-1);
    }
	return 0;

}