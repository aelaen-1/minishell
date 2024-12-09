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

int     handle_squote(char *s, int *i, t_parse_context *context, char **err_msg)
{
    int     j;
    int     start;
    int     count_squote;

    j = 0;
    start = *i;
    count_squote = count_quotes(s, start, SIMPLE_QUOTE);
    if (count_squote % 2 == 0)
    {
        start = *i + 1;
        while(s[start])
        {
            if (s[start] == SIMPLE_QUOTE)
                start++;
            else
            {
                context->last_token[j] = s[start];
                j++;
                start++;
            }
        }
        return((context->last_token[j] = 0), start + 1);
    }
    *err_msg = "squote>\n";
    return (0);
}

int handle_dquote(char *s, int *i, t_parse_context *context, char **err_msg)
{
    int     j;
    int     start;
    int     count_dquote;

    j = 0;
    start = *i;
    // compter le nb de double quotes
    count_dquote = count_quotes(s, start, DOUBLE_QUOTE);
    // si c'est pair on saute tout ceux qu'il y a l'interieur
    if (count_dquote % 2 == 0)
    {
        start = *i + 1;
        while(s[start])
        {
            if (s[start] == DOUBLE_QUOTE)
                start++;
            else
            {
                context->last_token[j] = s[start];
                j++;
                start++;
            }
        }
        return((context->last_token[j] = 0), start + 1);
    }
    *err_msg = "dquote>\n";
    return (0);
}