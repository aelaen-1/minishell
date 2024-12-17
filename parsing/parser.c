#include "../include/minishell.h"

char *ft_strchr(char *start, char to_find)
{
    int i = 0;
    while(*start != to_find && start != NULL)
    {
        if (*start == to_find)
            return (start + i);
        i++;
    }
    return (NULL);
}

t_token    **find_token(const t_token **start, const t_token **end, t_token_type token_type)
{   
    // cherche le token de type token_type, 
    while((*start)->type != token_type)
        start++;
    if ((*start)->type == token_type)
}

t_pipeline  *parse_pipeline(const t_token **start, const t_token **end)
{
    parse_command(start, find_token(start, end, ));
}

t_pipeline  *parse_command(const t_token **start, const t_token **end)
{

}
// pas de besoin de passer l'array par pointeur car pas de modification dans l'array
t_program   *parse_program(t_token_array array)
{
    t_program   *program;

    program = malloc(sizeof(t_program));
    program->pipeline = parse_pipeline(array.tokens, array.tokens + array.count);
    return (program);
}