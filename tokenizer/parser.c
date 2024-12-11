#include "../include/minishell.h"

int    init_token_array(t_token_array *array)
{
    array->count = 0;
    array->capacity = 4;
    array->tokens = malloc(array->capacity * sizeof(t_token *));
    return(array->tokens != NULL);
}


void    init_context(t_parse_context *context, char *input)
{
    context->input = input;
    context->input_len = ft_strlen(input);
    context->position = 0;
    context->last_token = NULL;
}

void	print_tokens(char *input)
{
    t_parse_context context;
    char    *err_msg;
    
    err_msg = NULL;
    init_token_array(context.array);
    init_context(&context, input);
    while (context.position < context.input_len)
    {
        get_next_token(&context, &err_msg);
        if (err_msg != NULL)
        {
            write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
            break;
        }
        printf("%s\n", context.last_token);
    }
    free_token_array(context.array);
}