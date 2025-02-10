/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:15:41 by glabaden          #+#    #+#             */
/*   Updated: 2025/02/10 14:16:25 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*create_command(size_t argc)
{
	size_t		i;
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->argv = malloc(sizeof(char *) * (argc + 1));
	if (!command->argv)
		return (free(command), NULL);
	i = 0;
	while (i <= argc)
		command->argv[i++] = NULL;
	command->redir_in.type = REDIR_NONE;
	command->redir_out.type = REDIR_NONE;
	command->redir_in.file = NULL;
	command->redir_out.file = NULL;
	command->index = 0;
	command->pipeline = NULL;
	command->fds[0] = 0;
	command->fds[1] = 1;
	return (command);
}

static int	handle_redirections(t_command *command, t_token ***iter,
		t_token **end, t_token **cmd_start)
{
	int	redir;

	redir = parse_redir(command, *iter, end, cmd_start);
	if (redir == 2)
		return (2);
	if (redir == 1)
	{
		*iter += 2;
		return (1);
	}
	if (redir == -1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putstr_fd("`newline'\n", 2);
		return (-1);
	}
	return (0);
}

static void	add_token_to_argv(t_token ***iter, t_command *command, size_t *i)
{
	if (!*iter || !**iter || !(**iter)->value)
		return ;
	command->argv[*i] = ft_strdup((**iter)->value);
	(*i)++;
	(*iter)++;
}

t_command	*parse_command(t_token **start, t_token **end)
{
	t_command	*command;
	t_token		**iter;
	size_t		i;
	int			redir;

	i = 0;
	iter = start;
	command = create_command(end - start);
	if (!command)
		return (0);
	redir = 0;
	while (iter < end)
	{
		redir = handle_redirections(command, &iter, end, start);
		if (redir == 1)
			continue ;
		if (redir == -1)
			return (destroy_command(command), NULL);
		if (redir == 2)
			add_token_to_argv(&iter, command, &i);
		command->argv[i++] = ft_strdup((*iter)->value);
		iter++;
	}
	return (command->argv[i] = NULL, command);
}

void	destroy_command(t_command *command)
{
	if (!command)
		return ;
	close_command_fds(command);
	if (command->redir_in.file)
		free(command->redir_in.file);
	if (command->redir_out.file)
		free(command->redir_out.file);
	free_command_argv(command->argv);
	free(command);
}
