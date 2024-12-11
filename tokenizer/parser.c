#include "../include/minishell.h"

void	print_tokens(char *input)
{
    t_parse_context context;

    init_token_array(&context.array);
    init_context(&context, input);
    while (context.position < context.input_len)
    {
        t_token *last_token = get_next_token(&context);
        // if (err_msg != NULL)
        // {
        //     write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
        //     break;
        // }
        printf("%s\n", last_token->value);
    }
    free_token_array(&context.array);
}