#include "../include/minishell.h"

void	print_tokens(char *input)
{
    t_parse_context context;
    int     i;
    int     len;
    char    *err_msg = NULL;

    i = 0;
    len = ft_strlen(input);
    context.last_token = malloc(len + 1);
    while (i < len)
    {
        i += get_next_token(input + i, &context, &err_msg);
        if (err_msg != NULL)
        {
            write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
            break;
        }
        printf("%s\n", context.last_token);
    }
    free(context.last_token);
}