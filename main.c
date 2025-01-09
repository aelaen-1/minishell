#include "include/minishell.h"
//REPL
//./minishell --pp (print_program)
int main (int ac, char **av)
{
    (void)ac;
    (void)av;
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
        parse_program(tokens);
        destroy_tokens_array(&tokens);
    }
    return 0;
}