#include "../include/minishell.h"

void	print_tokens(char *input)
{
    t_parse_context context;
    t_token         *last_token;
    if(!init_token_array(&context.array))
    {
        printf("array allocation failed\n");
        return ;
    }
    init_context(&context, input);
    while (context.position < context.input_len)
    {
        last_token = get_next_token(&context);
        printf("input : %s\n", context.input);
        printf("%s\n", last_token->value);
        printf("waiting for next token :\n");
    }
    free_token_array(&context.array);
}