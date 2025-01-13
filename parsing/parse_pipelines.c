#include "../include/minishell.h"

// compte le nombre de pipes entre start et end
static  size_t  count_pipes(t_token **start, t_token **end)
{
    size_t  i;

    i = 0;
    while (start < end)
    {
        if ((*start)->type == TOKEN_PIPE)
            i++;
        start++;
    }
    return (i);
}

// trouve le prochain token de type token_type, utilise ici pour trouver le prochain token de type PIPE
// et donc de delimiter notre commande actuelle
static t_token    **find_token(t_token **start, t_token **end, t_token_type token_type)
{   
    while (start < end)
   {
        if ((*start)->type == token_type)
            return (start);
        start++;
   }
   return (end);
}

// récupère les commandes entre chaque pipeline (pipeline->commands[i])
// en appellant parse_command(), fonction qui retourne un (t_command *)
t_pipeline  *parse_pipeline(t_token **start, t_token **end, t_env_node *envp)
{
    t_pipeline *pipeline;
    size_t  i;

    i = 0;
    pipeline = malloc(sizeof(t_pipeline));
    if (!pipeline)
        return (NULL);
    pipeline->cmd_count = count_pipes(start, end) + 1;
    pipeline->commands = malloc(sizeof(t_command *) * pipeline->cmd_count);
    if (!pipeline->commands)
        return (free(pipeline), NULL); 
    while (start < end && i < pipeline->cmd_count)
    {
        t_token **command_end = find_token(start, end, TOKEN_PIPE);
        pipeline->commands[i] = parse_command(start, command_end, envp);
        if (!pipeline->commands[i])
        {
            while (i > 0)
                free(pipeline->commands[i--]);
            free(pipeline->commands);
            free(pipeline);
            return (NULL);
        }
        start = command_end + 1;
        i++;
    }
    return (pipeline);
}