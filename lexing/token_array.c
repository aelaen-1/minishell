#include "../include/minishell.h"

t_token     *create_token(size_t max_size)
{
    t_token     *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = TOKEN_WORD;
    token->length = 0;
    token->is_builtin = 0;
    token->value = malloc(max_size);
    if (!token->value)
        return (free(token), NULL);
    ft_bzero(token->value, max_size);
    return (token);
}
// growing array function
t_token    *add_token(t_token_array *array, t_token *token)
{
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

void	print_tokens(t_token_array *array)
{
    size_t  i;

    i = 0;
    while (i < array->count)
    {
        printf("%s\n", array->tokens[i]->value);
        i++;
    }
}

void    find_token_type(t_token *token)
{
    if (!ft_strcmp(token->value, "|"))
        token->type = TOKEN_PIPE;
    else if (!ft_strcmp(token->value, "<"))
        token->type = TOKEN_REDIR_IN;
    else if (!ft_strcmp(token->value, ">"))
        token->type = TOKEN_REDIR_OUT;
    else if (!ft_strcmp(token->value, "<<"))
        token->type = TOKEN_HEREDOC;
    else if (!ft_strcmp(token->value, ">>"))
        token->type = TOKEN_APPEND;
    else
        token->type = WORD; 
}

// int     is_builtin(t_token  *token)
// {
//     if (!ft_strcmp(token->value, "echo"))
//         token->builtin = ECHO;
//     else if (!ft_strcmp(token->value, "cd"))
//         token->builtin = CD;
//     else if (!ft_strcmp(token->value, "pwd"))
//         token->builtin = PWD;
//     else if (!ft_strcmp(token->value, "export"))
//         token->builtin = EXPORT;
//     else if (!ft_strcmp(token->value, "unset"))
//         token->builtin = UNSET;  
//     else if (!ft_strcmp(token->value, "env"))
//         token->builtin = ENV;
//     else if (!ft_strcmp(token->value, "exit"))
//         token->builtin = EXIT;
//     else
//         return (0);
//     token->is_builtin = 1;
//     return (1);
// }
