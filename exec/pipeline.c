#include "../include/minishell.h"

void	pipeline_execution(t_program *program)
{
	pid_t	pid[200];
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < program->pipeline->cmd_count)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			exec_cmd(program->pipeline->commands[i], program);
		i++;
	}
	while (j < i)
	{
		waitpid(pid[j], NULL, 0);
		j++;
	}
}
