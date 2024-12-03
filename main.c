#include "include/minishell.h"


// REPL
int main (int ac, char **av)
{
    (void)ac;
    (void)av;
    char *cmd = readline("minishell % ");

    // pourquoi ça s'arrete après chaque input au lieu de boucler à l'infini ?
    while(cmd)
    {
        exec_cmd(cmd);
        cmd = readline("minishell % ");
    }
    return 0;
}