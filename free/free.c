#include "include/minishell.h"

void free_command(t_command *command) 
{
	int i;

	i = 0;
    if (!command)
        return;
    if (command->argv) {
        while (command->argv[i])
		{
			free(command->argv[i]);
			i++;
		}
        free(command->argv);
    }
    free(command);
}
void free_env_node(t_env_node *node) 
{
    t_env_node *temp;

    while (node) {
        temp = node->next;
        free(node->env_var);
        free(node);
        node = temp;
    }
}

void free_pipeline(t_pipeline *pipeline) 
{
    size_t i = 0;

	if (!pipeline)
        return;
	while(pipeline->cmd_count != i)
	{
        if (pipeline->commands[i])
            free_command(pipeline->commands[i]);
		i++;
	}
    free(pipeline->commands);
    free(pipeline);
}

void free_program( t_env_node *envp) 
{
	free_env_node(envp);
	rl_clear_history();
}