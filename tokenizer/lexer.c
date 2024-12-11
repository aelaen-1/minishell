#include "../include/minishell.h"

int get_next_token(t_parse_context *context, char **err_msg)
{
    char *s;
    int i = 0;

    s = context->input;
    context->last_token = add_new_token(context->array, ft_strlen(context->input)); // context->array et context.array donnent la même chose ? 
    while (s[context->position] && is_space(s[context->position]))
        context->position++;
    while(s[context->position])
    {
        if (is_space(s[context->position]))
            break ;
        if (s[context->position] == SIMPLE_QUOTE)
        {
            char *start_quote = s + context->position + 1;
            char *next_quote = ft_strchr(start_quote, SIMPLE_QUOTE);
            if (next_quote != NULL)
            {
                size_t  quote_len = next_quote - start_quote; // soustraction de pointeurs -> size_t
                ft_memcpy(context->last_token, start_quote, quote_len); // context->last_token + j  ?
                context->position += quote_len;
            }
            else
                return(*err_msg = UNCLOSED_QUOTE, context->position);
        }
        else if (s[context->position] == DOUBLE_QUOTE)
        {
            char *start_dquote = s + context->position + 1;
            char *next_dquote = ft_strchr(start_dquote, DOUBLE_QUOTE);
            if (next_dquote != NULL)
            {
                size_t  quote_len = next_dquote - start_dquote;
                ft_memcpy(context->last_token->value, start_dquote, quote_len); // renvoie void* , ft_memcpy(context->last_token, start_quote, quote_len);
                context->position += quote_len;
            }
            else
                return(*err_msg = UNCLOSED_DOUBLE_QUOTE, context->position);
        }
        context->last_token->value[i] = s[context->position];
        context->position++;
        i++;
    }
    context->last_token->value[i] = 0;
    return (context->position);
}

// remplacer les j avec une focntion add to token, qui prend un char * et un nb de caractères et qui l'ajoute au token