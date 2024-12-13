#include "../include/minishell.h"

// add src to the end of dest
void    append_to_token(t_token *dest, char *src, size_t length)
{
    size_t  i;
    size_t  j;

    i = 0;
    while (dest->value[i])
        i++;
    j = 0;
    while (j < length)
    {
        dest->value[i] = src[j];
        i++;
        j++;
    }
    dest->length += length;
}

// saving chars in context->last_token until end of word
t_token *get_next_token(t_parse_context *context)
{
    char    *s;
    int is_dquoting;

    is_dquoting = 0;
    s = context->input;
    context->last_token = add_new_token(&context->array, context->input_len + 1);
    while (s[context->position] && is_space(s[context->position]))
        context->position++;
    while(s[context->position])
    {
        if (is_space(s[context->position])) // retrait du !is_dquoting && 
            break ;
        if (s[context->position] == SIMPLE_QUOTE) // retrait du !is_dquoting && 
            if (handle_squote(s + context->position + 1, context))
                continue ;
        if (s[context->position] == DOUBLE_QUOTE) // gestion differente pour le $expand
        {
            if (is_dquoting || ft_strchr(s + context->position + 1, DOUBLE_QUOTE))
            {
                is_dquoting = !is_dquoting;
                context->position++;
                continue ;
            }
        }
        if (s[context->position] == PIPE || s[context->position] == LESS || s[context->position] == GREAT)
        { 
            if (context->last_token->length > 0)
                break;
            if ((s[context->position] == LESS && s[context->position + 1] == LESS) || (s[context->position] == GREAT && s[context->position + 1] == GREAT))
            {
                append_to_token(context->last_token, s + context->position, 1);
                context->position++;
            }
            append_to_token(context->last_token, s + context->position, 1);
            context->position++;
            return (context->last_token);
        }
        append_to_token(context->last_token, s + context->position, 1);
        context->position++;
    }
    append_to_token(context->last_token, "\0", 1);
    return (context->last_token);
}
