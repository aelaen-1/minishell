#include "../include/minishell.h"

int	**malloc_fds(t_pipeline *pipeline)
{
	size_t	i;
	int	**fds;

	i = 0;
	fds = malloc(sizeof(int *) * (pipeline->cmd_count) + 1);
	if (!fds)
	{
		fprintf(stderr, "fds malloc error\n");
		return (0); 
	}
	while (i < pipeline->cmd_count)
	{
		fds[i] = malloc (sizeof(int) * 2);
		if (!fds[i])
		{
			fprintf(stderr, "fd malloc error\n");
			return (0); 
		}
		fds[i][0] = -1;
		fds[i][1] = -1;
		i++;
	}
	fds[i] = 0;
	return (fds);
}

int	*malloc_pids(t_pipeline *pipeline)
{
	int	*pids;
	size_t	i;

	i = 0;
	pids = malloc(sizeof(int) * (pipeline->cmd_count + 1));
	if (!pids)
	{
		fprintf(stderr, "pids malloc error\n");
		return (0); 
	}
	while (i < pipeline->cmd_count)
	{
		pids[i] = 0;
		i++;
	}
	pids[i] = 0;
	return (pids);
}


void	free_fds(int **fds, size_t	command_count)
{
	size_t	i;

	i = 0;
	while (i < command_count)
	{
		free(fds[i]);
		i++;
	}
	free(fds);
}