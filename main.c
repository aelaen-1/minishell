#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_program		*prg;
	t_env_node		*envp;
	char			*input;
	t_token_array	tokens;

	(void)ac;
	(void)av;
	envp = init_env(env);
	while (1)
	{
		input = readline("minishell % ");
		if (*input)
			add_history(input);
		tokens = tokenize_input(input);
		prg = parse_program(tokens, envp);
		pipeline_execution(prg);
		destroy_tokens_array(&tokens);
	}
	return (0);
}
