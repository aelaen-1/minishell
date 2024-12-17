/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvastel <lvastel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:30:52 by lvastel           #+#    #+#             */
/*   Updated: 2024/12/15 20:26:23 by lvastel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// $ followed by characters in parentheses



// $ followed by characters



// $ followed by ?



// $ pseudo code

/*  if token starts with $ skip 1 ahead 
    use getenv on whatever is left of the string
    if getenv gets a result return its result
    else return newline
*/

int	ft_expand(t_token *token)
{
	const char	*env_variable;
	char	*value;

	env_variable = (char *)token + 1;
	value = getenv(env_variable);
	if (value)
		printf("%s\n", value);
	else
		printf("\n");
	return (0);
}
