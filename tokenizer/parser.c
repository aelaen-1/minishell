#include "../include/minishell.h"

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