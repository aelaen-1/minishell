#include "../include/minishell.h"

int	builtin_echo(t_command *command)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	if (!command->argv[i])
		return (ft_putchar_fd('\n', command->fds[1]), 0);
	while (command->argv[i] && !ft_strcmp("-n", command->argv[i]))
	{
		n_option = 1;
		i++;
	}
	while (command->argv[i])
	{
		ft_putstr_fd(command->argv[i], command->fds[1]);
		if (command->argv[i + 1])
			ft_putchar_fd(' ', command->fds[1]);
		i++;
	}
	if (n_option == 0)
		ft_putchar_fd('\n', command->fds[1]);
	return (0);
}
