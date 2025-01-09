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

// returns a token when end of word
t_token *get_next_token(t_lex_context *context)
{
    char    *s;
    t_token *last_token;

    s = context->input;
    last_token = create_token(context->input_len + 1);
    eat_spaces(context);
    while(s[context->position])
    {
        if(eat_spaces(context))
            break;
        if (s[context->position] == SIMPLE_QUOTE || s[context->position] == DOUBLE_QUOTE)
            if (handle_quote(s + context->position, last_token, context))
                continue ;
        if ((s[context->position] == PIPE || s[context->position] == LESS || s[context->position] == GREAT))
        { 
            if (last_token->length > 0)
                break;
            if ((s[context->position] == LESS && s[context->position + 1] == LESS) || (s[context->position] == GREAT && s[context->position + 1] == GREAT))
            {
                append_to_token(last_token, s + context->position, 1);
                context->position++;
            }
            append_to_token(last_token, s + context->position, 1);
            context->position++;
            find_token_type(last_token);
            return (last_token);
        }
        append_to_token(last_token, s + context->position, 1);
        context->position++;
    }
    append_to_token(last_token, "\0", 1);
    find_token_type(last_token);
    return (last_token);
}


t_token_array   tokenize_input(char *input)
{
    t_token_array   tokens;
    t_lex_context   context;

    if(!init_token_array(&tokens))
        return (tokens);
    init_lex_context(&context, input);
    while(context.position < context.input_len)
        add_token_to_array(&tokens, get_next_token(&context));
    return (tokens);
}
