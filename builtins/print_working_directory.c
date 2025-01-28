#include "../include/minishell.h"

int	builtin_pwd(t_command *command, t_context *context)
{
	char	*working_directory;

	working_directory = getcwd(NULL, 0);
	ft_putstr_fd(working_directory, command->fds[1]);
	ft_putchar_fd('\n', command->fds[1]);
	free(working_directory);
	context->last_cmd_status = 0;
	return (0);
}
