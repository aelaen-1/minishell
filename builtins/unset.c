#include "../include/minishell.h"

int	builtin_unset(t_command *command,  t_context *context)
{
	if (!command->argv[1])
		return (write(1, "unset: not enough arguments\n", 28), 1);
	else
	{
		size_t i = 1;
		while (command->argv[i])
		{
			if (!is_valid_identifier(command->argv[i]))
			{
				ft_putstr_fd("minishell: unset: `", 2);
				ft_putstr_fd(command->argv[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				return (1);
			}
			else
				unset_env(&context->envp, command->argv[i]);
			i++;
		}
	}
	return (0);
}
