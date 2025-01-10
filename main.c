#include "include/minishell.h"
//REPL
//./minishell --pp(print_program)
int main (int ac, char **av , char **env)
{
    (void)ac;
    (void)av;
    t_program *prg;
    if (ac == 2 && !strcmp(av[1], "--pp"))
    {
        while (1)
        {
        char *input = readline("minishell % ");
        t_token_array tokens = tokenize_input(input);
        t_program *program = parse_program(tokens, env);
        print_program_to_dot(program);
        destroy_tokens_array(&tokens);
        }
        return 0;
    }
    while(1)
    {
        char *input = readline("minishell % ");
        // printf("%s\n", input);
        // t_quote_type *quoting = get_quote_state(input);
        // for (size_t i =0; i < ft_strlen(input); i++)
        //     printf("%d", quoting[i]);
        t_token_array tokens = tokenize_input(input);
        prg = parse_program(tokens, env);
        if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "echo"))
            builtin_echo(prg->pipeline->commands[0]);
        else if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "env"))
            builtin_env(prg->pipeline->commands[0]);
        else if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "pwd"))
            builtin_pwd();
        else if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "cd"))
            builtin_cd(prg->pipeline->commands[0]);
        destroy_tokens_array(&tokens);
    }
    return 0;
}