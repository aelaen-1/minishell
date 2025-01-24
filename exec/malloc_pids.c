#include "../include/minishell.h"

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
		pids[i] = -1;
		i++;
	}
	pids[i] = 0;
	return (pids);
}
