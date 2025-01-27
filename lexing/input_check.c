#include "../include/minishell.h"

static int  is_redir(char c)
{
    if (c == '<' || c == '>')
        return (1);
    return (0);
}
static bool empty_input(char *input)
{
    size_t  i;
    size_t  len;

    if (!(*input))
        return (true);
    else
        add_history(input);
    len = ft_strlen(input);
    i = 0;
    while (i < len && is_space(input[i]))
        i++;
    if (i == len)
        return (true);
    return (false);
}
bool   pipe_error(char *s)
{
    size_t  i;
    size_t  len;
    size_t tmp;

    tmp = 0;
    i = 0;
    len = ft_strlen(s);
    while (s[i] && is_space(s[i]))
        i++;
    while (s[i])
    {
        if (s[i] == '|')
        {
            i++;
            if (i == len)
                return (ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2), true);
            tmp = i;
            while (s[i] && s[i] != '|')
            {
                if (is_redir(s[i]))
                    tmp++;
                i++;
            }
            if (i == tmp || tmp == len)
                return (ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2), true);
            i = tmp;
        }
        i++;
    }
    return (false);
}


bool    check_input(char *input, t_context *context)
{
    if (empty_input(input) || pipe_error(input))
    {
        context->last_cmd_status = 2;
        return (false);
    }
    return (true);
}