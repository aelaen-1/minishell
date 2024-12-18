#include "../include/minishell.h"

// compte le nombre de pipes entre start et end
static  size_t  count_pipes(t_token **start, t_token **end)
{
    size_t  i;

    i = 0;
    while (start < end)
    {
        if ((*start)->value[0] ==  '|')
            i++;
        start++;
    }
    // while (start < end) // ne reconnait pas les pipes (problème de type probablement)
    // {
    //     if ((*start)->type == TOKEN_PIPE)
    //     {
    //         printf("pipe found\n");
    //         i++;
    //     }
    //     start++;
    // }
    printf("pipes count: %zu\n", i);
    return (i);
}

// cherche le prochain token de type token_type
// t_token    **find_token(t_token **start, t_token **end, t_token_type token_type)
// {   
//     while (start < end)
//    {
//         if ((*start)->type == token_type)
//             return (start);
//         start++;
//    }
//    return (end);
// }

t_token    **find_token(t_token **start, t_token **end, char c)
{   
    while (start < end)
   {
        if ((*start)->value[0] == c)
            return (start);
        start++;
   }
   return (end);
}
// {   
//     while (start < end)
//    {
//         if ((*start)->type == token_type)
//             return (start);
//         start++;
//    }
//    return (end);
// }

// renvoie une structure pipeline composee de chaques commandes entre les pipes
// tant qu'on a pas atteint la fin du pipeline (A | B | C par ex => la fin est apres C, find_token renvoie NULL(char apres C))
t_pipeline  *parse_pipeline(t_token **start, t_token **end)
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
        t_token **command_end = find_token(start, end, '|');
        pipeline->commands[i] = parse_command(start, command_end);
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

t_command  *parse_command(t_token **start, t_token **end)
{
    size_t  i;
    size_t  argc;
    t_command   *command;

    i = 0;
    argc = end - start;
    command = malloc(sizeof(t_command));
    if (!command)
        return (NULL);
    command->argv = malloc(sizeof(char) * argc + 1);
    if (!command->argv)
        return (free(command), NULL);
    while(start < end)
    {
        command->argv[i] = (*start)->value;
        start++;
        i++;
    }
    command->argv[i] = NULL;
    i = 0;
    while(command->argv[i])
    {
        printf("%s ",command->argv[i]);
        i++;
    }
    printf("\n");
    return (command);
}

// ce programme comporte la structure pipeline s'il y en a une
// pas de besoin de passer l'array par pointeur car pas de modification dans l'array
t_program   *parse_program(t_token_array array)
{
    t_program   *program;

    program = malloc(sizeof(t_program));
    program->pipeline = parse_pipeline(array.tokens, array.tokens + array.count);
    return (program);
}
