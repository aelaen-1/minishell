#include "include/minishell.h"

extern int		g_sig;


static void	init_program_context(t_context *context, t_env_node *envp)
{
	context->envp = envp;
	context->last_cmd_status = 0;
	signal_handler();
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

static	void	ctrlc_exit_status(t_context *context)
{
	context->last_cmd_status = 130;
	g_sig = 0;
}

static	void	shell_repl_loop(t_context *context)
{
	char	*input;
	t_token_array	tokens;
	t_program	*program;

	g_sig = 0;
	while (1)
	{
		input = readline("minishell % ");
		if (g_sig)
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
		if(program)
		{
			execute_program(program, context);
			free_program(program);
		}
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env_node		*shell_env;
	t_context	context;

	(void)ac;
	(void)av;
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
