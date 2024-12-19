#include "include/minishell.h"

// REPL
int main (int ac, char **av)
{
    (void)ac;
    (void)av;
    while(1)
    {
        char *input = readline("minishell % ");
        t_token_array tokens = tokenize_input(input);
        parse_program(tokens);
        // print_tokens(&tokens);
        destroy_tokens_array(&tokens);
    }
    return 0;
}