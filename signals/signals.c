#include "../include/minishell.h"

int g_sig = 0;

void handle_ctrlc()
{
    write(1, "\n", 1);
    rl_replace_line("",0);
    rl_on_new_line();
    if (g_sig != 2)
        rl_redisplay();
    g_sig = 1;

}

void handle_ctrlslash()
{
    rl_replace_line(" ",1);
}

void signal_handler()
{
    signal(SIGINT,  handle_ctrlc);
    signal(SIGQUIT, handle_ctrlslash);
}

