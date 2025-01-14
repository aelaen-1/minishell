#include "../include/minishell.h"

int	builtin_env(t_command *command)
{
	t_env_node	*loop;
	
	if(!command || !command->envp)
		return 0;
	
	loop = command->envp;
	while (loop)
	{
		ft_putstr_fd(loop->env_var, 1);
		ft_putchar_fd('\n', 1);
		loop = loop->next;
	}
	return (0);
}