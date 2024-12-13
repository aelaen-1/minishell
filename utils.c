#include "include/minishell.h"

int is_space(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

void free_split(char **s)
{
    int i = 0;
    while (s[i])
    {
        free(s[i]);
        i++;
    }
    free(s);
    s = NULL;
}

void    destroy_tokens_array(t_token_array *array)
{
    size_t     i; 

    i = 0;
    while (i < array->count)
    {
        free(array->tokens[i]);
        i++;
    }
    free(array->tokens);
    array->tokens = NULL;
}

size_t  eat_spaces(t_parse_context *context)
{
    size_t  spaces;

    spaces = 0;
    while(is_space(context->input[context->position]))
        context->position++;
    return (spaces);
}