#include "../include/minishell.h"

int g_is_reading_line = 0;

void handle_ctrlc()
{
    write(1, "\n",1);
    if (g_is_reading_line == 1)
    {    
        rl_replace_line("",0);
        rl_on_new_line();
        rl_redisplay();
    }
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

