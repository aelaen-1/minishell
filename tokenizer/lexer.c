#include "../include/minishell.h"

int		get_next_token(char *s, struct parse_context *context, char **err_msg)
{
    int i = 0;
    int j = 0;

    while (s[i] && is_space(s[i]))
        i++;
    while(s[i] && !is_space(s[i]))
    {
        if (s[i] == SIMPLE_QUOTE)
            return (handle_squote(s, &i, context, err_msg));
        else if (s[i] == DOUBLE_QUOTE)
            return (handle_dquote(s, &i, context, err_msg));
        context->last_token[j] = s[i];
        i++;
        j++;
    }
    context->last_token[j] = 0;
    return (i);
}
