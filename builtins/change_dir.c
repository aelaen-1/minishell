#include "../include/minishell.h"

int	builtin_cd(t_command *command, t_context *context)
{
	char	*alternate_path;
	char	*former_path;

	former_path = getcwd(NULL, 0);
	if (!command->argv[1])
	{
		alternate_path = get_env_value("HOME", context->envp);
		if (!alternate_path)
			return (free(former_path),ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else if (command->argv[2])
	{
		free(former_path);
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	}
	else
		alternate_path = command->argv[1];
	if (chdir(alternate_path) != 0)
	{
		free(former_path);
		return(perror("minishell: cd"), 1);

	}
	alternate_path = getcwd(NULL, 0);
	update_env(&context->envp, "OLDPWD", former_path);
	update_env(&context->envp, "PWD", alternate_path);
	free(alternate_path);
	free(former_path);
	return (0);
}
