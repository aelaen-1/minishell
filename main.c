/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:49:44 by glabaden          #+#    #+#             */
/*   Updated: 2025/02/10 14:16:49 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

extern int		g_sig;

static void	init_program_context(t_context *context, t_env_node *envp)
{
	context->envp = envp;
	context->last_cmd_status = 0;
	signal_handler();
	g_sig = 0;
}

static bool	is_empty_line(char *input)
{
	size_t	i;

	i = 0;
	while (input[i] && is_space(input[i]))
		i++;
	if (input[i] != '\0')
		return (false);
	return (true);
}

static	void	execute_and_free_program(t_program *program, t_context *context)
{
	execute_program(program, context);
	free_program(program);
}

static	void	shell_repl_loop(t_context *context)
{
	char			*input;
	t_token_array	tokens;
	t_program		*program;

	while (1)
	{
		signal_handler();
		input = readline("minishell % ");
		if (g_sig == 130)
			ctrlc_exit_status(context);
		if (!input)
			break ;
		if (is_empty_line(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokens = tokenize_input(input);
		program = parse_program(tokens);
		destroy_tokens_array(&tokens);
		if (program)
			execute_and_free_program(program, context);
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env_node		*shell_env;
	t_context		context;

	(void)ac;
	(void)av;
	if (isatty(STDIN_FILENO) == 0)
		return (0);
	shell_env = init_env(env);
	if (!shell_env)
	{
		ft_putstr_fd("Failed to initialized environment\n", 2);
		return (1);
	}
	init_program_context(&context, shell_env);
	shell_repl_loop(&context);
	rl_clear_history();
	free_env_node(shell_env);
	return (0);
}
