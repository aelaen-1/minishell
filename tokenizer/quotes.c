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

int     handle_squote(char *start_quote, t_parse_context *context)
{
    char *next_quote = ft_strchr(start_quote, SIMPLE_QUOTE);
    if (next_quote != NULL)
    {
        size_t  quote_len = next_quote - start_quote;
        append_to_token(context->last_token, start_quote, quote_len);
        context->position += quote_len + 2;
        return (1);
    }
    return (0);
}

int     handle_dquote(char *start_quote, t_parse_context *context, int *is_dquoting)
{
    if (*is_dquoting || ft_strchr(start_quote, DOUBLE_QUOTE))
    {
        *is_dquoting = !(*is_dquoting);
        context->position++;
        return (1);
    }
    return (0);
}
// int handle_dquote(char *s, int *i, t_parse_context *context, char **err_msg)
// {
//     int     j;
//     int     start;
//     int     count_dquote;

//     j = 0;
//     start = *i;
//     // compter le nb de double quotes
//     count_dquote = count_quotes(s, start, DOUBLE_QUOTE);
//     // si c'est pair on saute tout ceux qu'il y a l'interieur
//     if (count_dquote % 2 == 0)
//     {
//         start = *i + 1;
//         while(s[start])
//         {
//             if (s[start] == DOUBLE_QUOTE)
//                 start++;
//             else
//             {
//                 context->last_token[j] = s[start];
//                 j++;
//                 start++;
//             }
//         }
//         return((context->last_token[j] = 0), start + 1);
//     }
//     *err_msg = "dquote>\n";
//     return (0);
// }