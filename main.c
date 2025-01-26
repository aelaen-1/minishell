#include "include/minishell.h"


extern int		g_is_reading_line;

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
	signal_handler(&context.last_cmd_status);
	prg = NULL;
	while (1)
	{
		g_is_reading_line = 1;
		input = readline("minishell % ");
		g_is_reading_line = 0;
		if (!input)
			break ;
		if (*input)
			add_history(input);
		else
			continue ;
		tokens = tokenize_input(input);
		prg = parse_program(tokens);
		if(prg)
		{
			if (execute_program(prg, &context) == -1)
			{
				printf("error\n");
				//child process is here
				free_program(prg);
				destroy_tokens_array(&tokens);
				rl_clear_history();
				free(input);
				free_env_node(envp);
				return (0);
			}
			else
			{
				//parent process is here
				// printf("well executed\n");
				free_program(prg);
			}
		}
		destroy_tokens_array(&tokens);
		rl_clear_history();
		free(input);
	}
	free_env_node(envp);
	return (0);
}
