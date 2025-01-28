#include "../include/minishell.h"


static void	skip_n(t_command *command, size_t *i, int *n_option)
{
	while (command->argv[*i])
	{
		if (command->argv[*i][0] == '-' && command->argv[*i][1] == 'n')
		{
			size_t j = 2;
			while (command->argv[*i][j] == 'n')
				j++;
			if (command->argv[*i][j] == '\0')
			{
				(*n_option)++;
				(*i)++;
			}
			else
				break ;
		}
		else
			break ;
	}
}

int	builtin_echo(t_command *command, t_context *context)
{
	size_t	i;
	int	n_option;

	i = 1;
	n_option = 0;
	context->last_cmd_status = 0;
	if (!command->argv[i])
		return (ft_putchar_fd('\n', command->fds[1]), 0);
	skip_n(command, &i, &n_option);
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
