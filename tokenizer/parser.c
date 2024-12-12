#include "../include/minishell.h"

void	print_tokens(char *input)
{
    t_parse_context context;
<<<<<<< HEAD
    t_token         *last_token;
    if(!init_token_array(&context.array))
    {
        printf("array allocation failed\n");
        return ;
    }
=======
    t_token *last_token;

    init_token_array(&context.array);
>>>>>>> 134b91e (bonsoir)
    init_context(&context, input);
    while (context.position < context.input_len)
    {
        last_token = get_next_token(&context);
<<<<<<< HEAD
        printf("input : %s\n", context.input);
=======
>>>>>>> 134b91e (bonsoir)
        printf("%s\n", last_token->value);
        printf("waiting for next token :\n");
    }
    destroy_tokens_array(&context.array);
}