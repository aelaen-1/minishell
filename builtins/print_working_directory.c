#include "../include/minishell.h"

int	builtin_pwd()
{
	char *working_directory;

    working_directory = getcwd(NULL, 0);
    ft_putstr_fd(working_directory, 1);
    ft_putchar_fd('\n', 1);
    free(working_directory);
	return (0);
}