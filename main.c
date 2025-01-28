#include "include/minishell.h"

extern int		g_sig;


static void	init_program_context(t_context *context, t_env_node *envp)
{
	context->envp = envp;
	context->last_cmd_status = 0;
	signal_handler();
}

static	void	shell_repl_loop(t_context *context)
{
	char	*input;
	t_token_array	tokens;
	t_program	*program;
	int		should_loop;
	int		status;

	status = 0;
	should_loop = 1;
	while (should_loop)
	{
		g_sig = 0;
		input = readline("minishell % ");
		if (g_sig)
			context->last_cmd_status = 130;
		if (!input)
			break ;
		if (!check_input(input, context))
		{
			free(input);
			continue ;
		}
		tokens = tokenize_input(input);
		program = parse_program(tokens);
		if(program)
		{
			status = execute_program(program, context);
			if (status != 0)
				should_loop = 0;
			context->last_cmd_status = status;
			free_program(program);
		}
		destroy_tokens_array(&tokens);
		free(input);
		if (g_sig)
			context->last_cmd_status = 130;
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
		return (perror("Failed to initialize environment"), 1);
	init_program_context(&context, shell_env);
	shell_repl_loop(&context);
	// rl_clear_history();
	free_env_node(shell_env);
	return (0);
}
