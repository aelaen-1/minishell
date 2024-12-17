#include "../include/minishell.h"

// QUOTING RULES 


int     count_quotes(char *s, int start, char s_or_d)
{
    int     count;

    count = 0;
    if (s_or_d == SIMPLE_QUOTE)
    {
        while(s[start])
        {
            if (s[start] == SIMPLE_QUOTE)
                count++;
            start++;
        }
    }
    else
    {
        while (s[start])
        {
            if (s[start] == DOUBLE_QUOTE)
                count++;
            start++;
        }
    }
    return (count);
}

int     handle_quote(char *start_quote, t_token *token, t_lex_context *context)
{
    char *next_quote = ft_strchr(start_quote + 1, *start_quote);
    if (next_quote != NULL)
    {
        size_t  quote_len = next_quote - start_quote + 1;
        append_to_token(token, start_quote, quote_len);
        context->position += quote_len;
        return (1);
    }
    return (0);
}
