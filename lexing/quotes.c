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
// verifie si la quote trouvee (egale a start_quote) est fermee grace strchr
// si c'est le cas on ajoute le token qui part de start_quote (le quote ouvrant) au next_quote (le quote fermant), les deux inclus
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

static void    change_state_if_next_quote(char *s, t_quote_type *current, int first_quote_type)
{
    if (first_quote_type == SIMPLE_QUOTE)
    {
        if (ft_strchr(s, SIMPLE_QUOTE))
            *current = QUOTE_SINGLE;
    }
    else
    {
        if (ft_strchr(s, DOUBLE_QUOTE))
            *current = QUOTE_DOUBLE;
    }
}

t_quote_type    *get_quote_state(char *s)
{
    t_quote_type *state;
    t_quote_type    current;
    size_t  i;

    i = 0;
    current = QUOTE_NONE;
    state = malloc(ft_strlen(s) * sizeof(t_quote_type));
    if (!state)
        return (NULL);
    while(s[i])
    {
        if (s[i] == SIMPLE_QUOTE && current == QUOTE_NONE)
            change_state_if_next_quote(s + i + 1, &current, SIMPLE_QUOTE);
        else if (s[i] == DOUBLE_QUOTE && current == QUOTE_NONE)
            change_state_if_next_quote(s + i + 1, &current, DOUBLE_QUOTE);
        else if (s[i] == SIMPLE_QUOTE && current == QUOTE_SINGLE)
            current = QUOTE_NONE;
        else if (s[i] == DOUBLE_QUOTE && current == QUOTE_DOUBLE)
            current = QUOTE_NONE;
        state[i] = current;
        i++;
    }
    return (state);
}
