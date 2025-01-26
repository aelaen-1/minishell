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

bool	check_start_end(char *s, char c, bool ends)
{
    size_t  i;

    i = 0;
    if (ends == true)
        i = 0;
    else
        i = ft_strlen(s) - 1;
    while (s[i] && is_space(s[i]))
    {
        if (ends == true)
            i++;
        else
            i--;
    }
    if (s[i] == c)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        ft_putchar_fd(c, 2);
        ft_putstr_fd("'\n", 2);
        return (true);
    }
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
            if (i == tmp)
                return (ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2), true);
        }
        i++;
    }
    return (false);
}

static  int check_access(char *path)
{
    if (access(path, F_OK) == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (1);
    }
}

bool    check_input(char *input, t_context *context)
{
    if ()
    if (empty_input(input) || check_start_end(input, '|', false) || check_start_end(input, '|', true)
        || check_start_end(input, '<', false) || check_start_end(input, '>', true))
    {
        context->last_cmd_status = 2;
        return (false);
    }
    return (true);
}
