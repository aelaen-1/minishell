/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glabaden <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:16:07 by glabaden          #+#    #+#             */
/*   Updated: 2025/01/31 10:16:09 by glabaden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_program	*parse_program(t_token_array array)
{
	t_program	*program;

	if (array.count == 0)
		return (NULL);
	program = malloc(sizeof(t_program));
	if (!program)
		return (NULL);
	program->pipeline = parse_pipeline(array.tokens,
			array.tokens + array.count);
	if (!program->pipeline)
		return (free(program), NULL);
	return (program);
}
