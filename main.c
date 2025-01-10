#include "include/minishell.h"
//REPL
//./minishell --p(print_program)
int main (int ac, char **av , char **env)
{
    (void)ac;
    (void)av;
    t_program *prg;
    if (ac == 2 && !strcmp(av[1], "--pp"))
    {
        char *input = readline("");
        t_token_array tokens = tokenize_input(input);
        t_program *program = parse_program(tokens);
        print_program_to_dot(program);
        destroy_tokens_array(&tokens);
        return (0);
    }
    while(1)
    {
        char *input = readline("minishell % ");
        // printf("%s\n", input);
        // t_quote_type *quoting = get_quote_state(input);
        // for (size_t i =0; i < ft_strlen(input); i++)
        //     printf("%d", quoting[i]);
        t_token_array tokens = tokenize_input(input);
        prg = parse_program(tokens);
        if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "echo"))
            builtin_echo(prg->pipeline->commands[0]->argv);
        else if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "env"))
            builtin_env(env);
        else if(!ft_strcmp(prg->pipeline->commands[0]->argv[0], "pwd"))
            builtin_pwd(env);
        destroy_tokens_array(&tokens);
    }
    return 0;
}