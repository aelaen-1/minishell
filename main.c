#include "include/minishell.h"

// pipes, redirections builtins, field splitting, arguments du main, and_or


void free_command(t_command *command) 
{
	int i;

	i = 0;
    if (!command)
        return;
    if (command->argv) {
        while (command->argv[i])
		{
			free(command->argv[i]);
			i++;
		}
        free(command->argv);
    }
    free(command);
}
void free_env_node(t_env_node *node) {
    t_env_node *temp;

    while (node) {
        temp = node->next;
        free(node->env_var);
        free(node);
        node = temp;
    }
}

void free_pipeline(t_pipeline *pipeline) {
    size_t i = 0;

	if (!pipeline)
        return;
	while(pipeline->cmd_count != i)
	{
        if (pipeline->commands[i])
            free_command(pipeline->commands[i]);
		i++;
	}
    free(pipeline->commands);
    free(pipeline);
}

void free_program( t_env_node *envp) 
{
	free_env_node(envp);
	rl_clear_history();
}


// virer l'argument program des fonctions qui ne l'utilisent pas car trop général. Donner envp pour être clair et limiter l'accès aux trucs inutiles
int	main(int ac, char **av, char **env)
{
	t_program		*prg;
	t_env_node		*envp;
	char			*input;
	t_token_array	tokens;
	t_expansion_context	context;

	(void)ac;
	(void)av;
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
		// expand_program(prg);
		// redirect_program(prg);
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
