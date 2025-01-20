#include "../include/minishell.h"

int	builtin_env(t_command *command, t_expansion_context *context)
{
	t_env_node	*loop;

	if (!command || !context->envp)
		return (0);
	loop = context->envp;
	while (loop)
	{
		ft_putstr_fd(loop->env_var, command->fds[1]);
		ft_putchar_fd('\n', command->fds[1]);
		loop = loop->next;
	}
	return (0);
}
 