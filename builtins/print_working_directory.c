#include "../include/minishell.h"

int	builtin_pwd(t_command *command)
{
	char	*working_directory;

	working_directory = getcwd(NULL, 0);
	ft_putstr_fd(working_directory, command->fds[1]);
	ft_putchar_fd('\n', command->fds[1]);
	free(working_directory);
	return (0);
}
