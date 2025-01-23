#include "../include/minishell.h"

void command_not_found_and_exit(char *arg, char *path, char **env)
{
    free(path);
    free_split(env);
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(": command not found\n", 2);
    exit(1);
}

