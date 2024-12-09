#include "include/minishell.h"
// REPL
int main (int ac, char **av)
{
    (void)ac;
    (void)av;

    while(true)
    {
        char *cmd = readline("minishell % ");
        print_tokens(cmd);
    }
    return 0;
}   