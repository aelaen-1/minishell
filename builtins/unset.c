#include "../include/minishell.h"

int	builtin_unset(t_command *command,  t_context *context)
{
	if (!command->argv[1])
		return (write(1, "unset: not enough arguments\n", 28), 1);
	else
		unset_env(&context->envp, command->argv[1]);
	return (0);
}
