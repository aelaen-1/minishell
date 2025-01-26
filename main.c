#include "include/minishell.h"

extern int		g_sig;

int	main(int ac, char **av, char **env)
{
	t_program		*prg;
	t_env_node		*envp;
	char			*input;
	t_token_array	tokens;
	t_context	context;

	(void)ac;
	(void)av;
	envp = init_env(env);
	context.envp = envp;
	context.last_cmd_status = 0;
	signal_handler();
	prg = NULL;
	int should_loop = 1;
	while (should_loop)
	{
		g_sig = 0;
		input = readline("minishell % ");
		if (g_sig)
			context.last_cmd_status = 130;
		if (!input)
			break ;
		if (!check_input(input, &context))
		{
			free(input);
			continue ;
		}
		tokens = tokenize_input(input);
		prg = parse_program(tokens);
		if(prg)
		{
			if (execute_program(prg, &context) == -1)
				should_loop = 0;
			free_program(prg);
		}
		destroy_tokens_array(&tokens);
		free(input);
		if (g_sig)
			context.last_cmd_status = 130;
	}
	rl_clear_history();
	free_env_node(envp);
	return (0);
}
