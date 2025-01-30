#include "../include/minishell.h"

int	builtin_unset(t_command *command, t_context *context)
{
	size_t	i;

	if (!command->argv[1])
		return (0);
	else
	{
		i = 1;
		while (command->argv[i])
		{
			unset_env(&context->envp, command->argv[i]);
			i++;
		}
	}
	return (0);
}
