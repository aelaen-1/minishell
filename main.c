#include "include/minishell.h"

// pipes, redirections builtins, field splitting, arguments du main, and_or

// virer l'argument program des fonctions qui ne l'utilisent pas car trop général. Donner envp pour être clair et limiter l'accès aux trucs inutiles
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
		if (input)
			add_history(input);
		tokens = tokenize_input(input);
		prg = parse_program(tokens, envp);
		expand_program(prg);
		redirect_program(prg);
		execute_program(prg);
		destroy_tokens_array(&tokens);
	}
	return (0);
}
