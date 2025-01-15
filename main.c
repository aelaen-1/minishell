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
		if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "echo"))
			builtin_echo(prg->pipeline->commands[0]);
		else if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "env"))
			builtin_env(prg->pipeline->commands[0]);
		else if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "pwd"))
			builtin_pwd();
		else if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "cd"))
			builtin_cd(prg->pipeline->commands[0]);
		else if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "export"))
			builtin_export(prg->pipeline->commands[0]);
		else if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "unset"))
			builtin_unset(prg->pipeline->commands[0]);
        else
        {
            // size_t i = 0;
            // while (i < prg->pipeline->cmd_count)
            // {
            //     exec_cmd(prg->pipeline->commands[i]);
            //     i++;
            // }
            exec_cmd(prg->pipeline->commands[0], env);
        }
        destroy_tokens_array(&tokens);
    }
    return 0;
}