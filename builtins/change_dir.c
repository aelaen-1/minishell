#include "../include/minishell.h"

static char	*get_alternate_path(t_command *command, t_context *context)
{
	char	*alternate_path;

	if (!command->argv[1])
	{
		alternate_path = get_env_value("HOME", context->envp);
		if (!alternate_path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else if (command->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (NULL);
	}
	else
		alternate_path = command->argv[1];
	return (alternate_path);
}

static int	change_directory(char *path)
{
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

static void	update_paths(t_context *context, char *former_path)
{
	char	*current_path;

	current_path = getcwd(NULL, 0);
	update_env(&context->envp, "OLDPWD", former_path);
	update_env(&context->envp, "PWD", current_path);
	free(current_path);
}

int	builtin_cd(t_command *command, t_context *context)
{
	char	*alternate_path;
	char	*former_path;

	former_path = getcwd(NULL, 0);
	alternate_path = get_alternate_path(command, context);
	if (!alternate_path)
	{
		free(former_path);
		return (1);
	}
	if (change_directory(alternate_path) != 0)
	{
		if (!command->argv[1])
			free(alternate_path);
		free(former_path);
		return (1);
	}
	if (!command->argv[1])
		free(alternate_path);
	update_paths(context, former_path);
	free(former_path);
	return (0);
}
