#include "include/minishell.h"

// pipes, redirections builtins, field splitting, arguments du main, and_or


// virer l'argument program des fonctions qui ne l'utilisent pas car trop général. Donner envp pour être clair et limiter l'accès aux trucs inutiles
int	main(int ac, char **av, char **env)
{
	t_program		*prg;
	t_env_node		*envp;
	char			*input;
	t_token_array	tokens;
	t_context	context;

	(void)ac;
	(void)av;
	signal_handler();
	envp = init_env(env);
	context.envp = envp;
	context.last_cmd_status = 0;
	prg = NULL;
	while (1)
	{
		input = readline("minishell % ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tokens = tokenize_input(input);
		prg = parse_program(tokens);
		if(!prg)
		{
			destroy_tokens_array(&tokens);
			break ;
		}
		execute_program(prg, &context);
		destroy_tokens_array(&tokens);
		free_pipeline(prg->pipeline);
		free(input);
	}
	if(prg)
		free(prg);
	free_program(envp);
	return (0);
}
