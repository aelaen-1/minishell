#include "../include/minishell.h"

int space_before_pipe(char *s, int *i, t_parse_context *context)
{
    // if (s[i] == PIPE)
    int j = 0;
    int index = *i;
    if (s[index - 1] && !is_space(s[index - 1]))
        return (0); // the last token isn't the pipe
    else if (s[index - 1] && is_space(s[index - 1]))
    {
        context->last_token[j] = PIPE;
        return (1);
    }
    context->last_token[j] = PIPE;
    return (-1);
}



int get_next_token(char *s, t_parse_context *context, char **err_msg)
{
    int i = 0;
    int j = 0;

    // context->quotes = NONE;
    while (s[i] && is_space(s[i]))
        i++;
    while(s[i] && !is_space(s[i]))
    {
        if (s[i] == SIMPLE_QUOTE)
            return (handle_squote(s, &i, context, err_msg));
        else if (s[i] == DOUBLE_QUOTE)
            return (handle_dquote(s, &i, context, err_msg));
        else if (s[i] == PIPE)
        {
            if((space_before_pipe(s, &i, context) == 1) != 0)
            {
                context->last_token[j] = s[i];
                return(context->last_token[++j] = 0, i + 1);
            }
            else
                return(context->last_token = 0, i);
        }

        context->last_token[j] = s[i];
        i++;
        j++;
    }
    context->last_token[j] = 0;
    return (i);
}
