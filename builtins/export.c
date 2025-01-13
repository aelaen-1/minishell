/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvastel <lvastel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:18:08 by lvastel           #+#    #+#             */
/*   Updated: 2024/12/13 13:18:10 by lvastel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int parse_key_value(char *input, char **key, char **value)
{
    int len_key;
    int len_value;
    char *separator;

    if(!(*input))
        return -1;
    separator = strchr(input, '=');
    if(!separator)
        return -2;
    len_key = separator - input;
    len_value = strlen(separator + 1);
    (*key) = (char *) malloc((len_key + 1) * sizeof(char));
    (*value) = (char *) malloc((len_value + 1) * sizeof(char));
    if(!(*key) || !(*value))
    {
        key = NULL;
        value = NULL;
        free(*key);
        free(*value);
        return -3;
    }
    ft_memcpy(*key, input, len_key);
    (*key)[len_key] = '\0';
    strcpy(*value, separator + 1);
    return 0;
}
int builtin_export(t_command *command)
{
    char *key;
    char *value;

    key = NULL;
    value = NULL;
    if(!command->argv[1])
        return (builtin_env(command),1);
    else
    {
        parse_key_value(command->argv[1],&key, &value);
        update_env(&command->envp,key,value);
    } 
    return 0;
}