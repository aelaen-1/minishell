#include "../include/minishell.h"

//              PIPE
// int space_before_pipe(char *s, int *i, t_parse_context *context)
// {
//     // if (s[i] == PIPE)
//     int j = 0;
//     int index = *i;
//     if (s[index - 1] && !is_space(s[index - 1]))
//         return (0); // the last token isn't the pipe
//     else if (s[index - 1] && is_space(s[index - 1]))
//     {
//         context->last_token[j] = PIPE;
//         return (1);
//     }
//     context->last_token[j] = PIPE;
//     return (-1);
// }
// else if (s[i] == PIPE)
// {
//     if((space_before_pipe(s, &i, context) == 1) != 0)
//     {
//         context->last_token[j] = s[i];
//         return(context->last_token[++j] = 0, i + 1);
//     }
//     else
//         return(context->last_token = 0, i);
// }


// remplacer les j avec une focntion add to token, qui prend un char * et un nb de caractères et qui l'ajoute au token
int get_next_token(t_parse_context *context, char **err_msg)
{
    int i = 0; // context->position
    int j = 0;
    char *s;

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
                j += quote_len;
                context->position += quote_len;
            }
            else
                context->last_token[j] = SIMPLE_QUOTE;
        }
        else if (s[i] == DOUBLE_QUOTE)
            return (handle_dquote(s, &i, context, err_msg));
        context->last_token[j] = s[context->position]; // faire add to token (s + i, 1)
        i++;
        j++;
    }
    context->last_token[j] = 0;
    return (i);
}

void    add_token_to_array(char *s, t_parse_context *context, size_t token_size)
{
    
}