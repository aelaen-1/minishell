#include "../include/minishell.h"

// growing array function
// fill struct token and realloc if array exceeds initial capacity

t_token    *add_new_token(t_token_array *array, size_t max_size)
{
    t_token     *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = NONE;
    token->length = 0;
    token->value = malloc(max_size);
    if (!token->value)
        return (free(token), NULL);
    if (array->count >= array->capacity)
    {
        t_token **new_tokens = malloc((array->capacity * 2) * sizeof(t_token *));
        if (!new_tokens)
        {
            free(token->value);
            free(token);
            return (NULL);
        }
        ft_memcpy(new_tokens, array->tokens, array->count * sizeof(t_token *)); // size of à vérifier (man memcpy)
        free(array->tokens);
        array->tokens = new_tokens;
        array->capacity *= 2; 
    }
    array->tokens[array->count] = token; 
    array->count++; 
    return (token);
}
