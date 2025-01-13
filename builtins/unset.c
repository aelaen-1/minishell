/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvastel <lvastel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:18:20 by lvastel           #+#    #+#             */
/*   Updated: 2024/12/13 13:18:21 by lvastel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int builtin_unset(t_command *command)
{
    if(!command->argv[1])
        return (write(1,"unset: not enough arguments\n",28),1);
    else
        unset_env(&command->envp, command->argv[1]);
    return 0;
}