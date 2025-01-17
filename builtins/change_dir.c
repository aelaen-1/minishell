#include "../include/minishell.h"

int	builtin_cd(t_command *command, t_program *program)
{
	char	*alternate_path;
	char	*former_path;

	former_path = getcwd(NULL, 0);
	if (!command->argv[1])
	{
		alternate_path = get_env_value("HOME", program);
		if (alternate_path == NULL)
			return (write(2, "cd: HOME not set\n", 17), -1);
	}
	else
		alternate_path = command->argv[1];
	if (chdir(alternate_path) != 0)
		return (perror("cd"), -1);
	alternate_path = getcwd(NULL, 0);
	update_env(&program->envp, "OLDPWD", former_path);
	update_env(&program->envp, "PWD", alternate_path);
	free(alternate_path);
	free(former_path);
	return (0);
}
