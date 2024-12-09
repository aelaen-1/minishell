#include "../include/minishell.h"


int     handle_squote(char *s, int *i, t_parse_context *context, char **err_msg)
{
    int     j;
    int     start;

    j = 0;
    start = *i + 1;
    while (s[start] && (s[start] != SIMPLE_QUOTE))
    {
        context->last_token[j] = s[start];
        j++;
        start++;
        if (s[start] && (s[start] == SIMPLE_QUOTE))
            return((context->last_token[j] = 0), start);
    }
    *err_msg = "quote>\n";
    return (0);
}

int handle_dquote(char *s, int *i, t_parse_context *context, char **err_msg)
{
    int     j;
    int     start;

    j = 0;
    start = *i + 1;
    while (s[start] && (s[start] != DOUBLE_QUOTE))
    {
        context->last_token[j] = s[start];
        j++;
        start++;
        if (s[start] && (s[start] == DOUBLE_QUOTE))
            return((context->last_token[j] = 0), start);
    }
    *err_msg = "dquote>\n";
    return (0);
}

int		get_next_token(char *s, struct parse_context *context, char **err_msg)
{
    int i = 0;
    int j = 0;

    while (s[i] && is_space(s[i]))
        i++;
    while(s[i] && !is_space(s[i]))
    {
        if (s[i] == SIMPLE_QUOTE)
        {
            context->last_token[j] = 0;
            printf("%s\n", context->last_token);
            return (handle_squote(s, &i, context, err_msg));
        }
        else if (s[i] == DOUBLE_QUOTE)
            return (handle_dquote(s, &i, context, err_msg));
        // else if (!ft_strncmp(s + i, "\", 1) // \
        // {

        // }
        context->last_token[j] = s[i];
        i++;
        j++;
    }
    context->last_token[j] = 0;
    return (i);
}

// que dans lexer.c : 
// implémenter une des règles du SCL, par les simple quotes,
// on break sur les simples quotes (on avance jusqu'au prochain)
// + backslash (on écrit le caractère juste après)