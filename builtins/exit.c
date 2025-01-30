#include "../include/minishell.h"

int	validate_exit_argument(char *arg)
{
	int	i;
	int	status;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) || arg[i] == '-' || arg[i] == '+')
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (2);
		}
		i++;
	}
	status = ft_atoi(arg);
	if (status > 255 || status < 0)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	return (status);
}

int	builtin_exit(t_command *command, t_context *context)
{
	int	status;

	status = 0;
	if (command->argv[1])
		status = validate_exit_argument(command->argv[1]);
	context->last_cmd_status = status;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	return (421);
}
