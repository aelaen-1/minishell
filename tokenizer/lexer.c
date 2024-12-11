#include "../include/minishell.h"

static void    append_to_token(t_token *dest, char *src, size_t length)
{
    ft_memcpy(dest->value, src, length);
    dest->length += length;
}

t_token *get_next_token(t_parse_context *context)
{
    char *s;

    int is_dquoting = 0;
    s = context->input;
    context->last_token = add_new_token(&context->array, context->input_len + 1);
    while (s[context->position] && is_space(s[context->position]))
        context->position++;
    while(s[context->position])
    {
        if (!is_dquoting && is_space(s[context->position]))
            break ;
        if (!is_dquoting && s[context->position] == SIMPLE_QUOTE)
        {
            char *start_quote = s + context->position + 1;
            char *next_quote = ft_strchr(start_quote, SIMPLE_QUOTE);
            if (next_quote != NULL)
            {
                size_t  quote_len = next_quote - start_quote;
                append_to_token(context->last_token, start_quote, quote_len);
                context->position += quote_len + 1;
                continue ; // ramène au début du while  sans passer par le reste des étapes
            }
        }
        if (s[context->position] == DOUBLE_QUOTE) // gestion differente pour le $expand
        {
            if (is_dquoting || ft_strchr(s + context->position + 1, DOUBLE_QUOTE))
            {
                is_dquoting = !is_dquoting;
                context->position++;
                continue ;
            }
        }
        append_to_token(context->last_token, s + context->position, 1);
        context->position++;
    }
    append_to_token(context->last_token, "\0", 1);
    return (context->last_token);
}
