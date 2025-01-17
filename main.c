#include "include/minishell.h"

//REPL 
int main (int ac, char **av , char **env)
{
    (void)ac;
    (void)av;
    t_program *prg;
    t_env_node *envp;

    envp = init_env(env);
    while(1)
    {
        char *input = readline("minishell % ");
		if (*input)
			add_history(input);
		t_token_array tokens = tokenize_input(input);
		prg = parse_program(tokens, envp);
        pipeline_execution(prg);
        destroy_tokens_array(&tokens);
    }
    return 0;
}
