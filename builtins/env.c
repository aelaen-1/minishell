#include "../include/minishell.h"

int	builtin_env(char **env)
{
	int	i;
	
	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}