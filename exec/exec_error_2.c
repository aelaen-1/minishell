#include "../include/minishell.h"

int	exec_permission(char *cmd, t_context *context, struct stat path_stat)
{
	if (S_ISREG(path_stat.st_mode) && access(cmd, X_OK) == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			context->last_cmd_status = 126;
			return (126);
		}
	}
	return (0);
}
