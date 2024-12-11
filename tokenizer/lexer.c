#include "../include/minishell.h"

static void    append_to_token(t_token *dest, char *src, size_t length)
{
    ft_memcpy(dest->value, src, length);
    dest->length += length;
}

t_token *get_next_token(t_parse_context *context)
{
    char *s;

    int is_quoting = 0; // dquote
    s = context->input;
    context->last_token = add_new_token(&context->array, context->input_len + 1); // context->array et context.array donnent la même chose ? 
    while (s[context->position] && is_space(s[context->position]))
        context->position++;
    while(s[context->position])
    {
        if (!is_quoting && is_space(s[context->position]))
            break ;
        if (!is_quoting && s[context->position] == SIMPLE_QUOTE)
        {
            char *start_quote = s + context->position + 1;
            char *next_quote = ft_strchr(start_quote, SIMPLE_QUOTE);
            if (next_quote != NULL)
            {
                size_t  quote_len = next_quote - start_quote; // soustraction de pointeurs -> size_t
                append_to_token(context->last_token, start_quote, quote_len); // context->last_token + j  ?
                context->position += quote_len + 1;
                continue ; // ramène au début du while  sans passer par le reste des étapes
            }
        }
        if (s[context->position] == DOUBLE_QUOTE)
        {
            if (is_quoting || ft_strchr(s + context->position + 1, DOUBLE_QUOTE))
            {
                is_quoting = !is_quoting;
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


// else if (s[context->position] == DOUBLE_QUOTE)
// {
//     char *start_dquote = s + context->position + 1;
//     char *next_dquote = ft_strchr(start_dquote, DOUBLE_QUOTE);
//     if (next_dquote != NULL)
//     {
//         size_t  quote_len = next_dquote - start_dquote;
//         ft_memcpy(context->last_token->value, start_dquote, quote_len); // renvoie void* , ft_memcpy(context->last_token, start_quote, quote_len);
//         context->position += quote_len;
//     }
//     else
//         return(*err_msg = UNCLOSED_DOUBLE_QUOTE, context->position);
// }