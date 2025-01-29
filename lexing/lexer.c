#include "../include/minishell.h"

static void	append_and_shift(t_token *token, t_lex_context *context)
{
	append_to_token(token, context->input + context->position, 1);
	context->position += 1;
}

static t_token	*finalize_token(t_token *token)
{
	if (token->length == 0)
	{
		free(token->value);
		free(token);
		return (NULL);
	}
	append_to_token(token, "\0", 1);
	find_token_type(token);
	return (token);
}

void	append_to_token(t_token *dest, char *src, size_t length)
{
	size_t	i;
	size_t	j;

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

t_token	*get_next_token(t_lex_context *context)
{
	char	*s;
	t_token	*last_token;

	s = context->input;
	last_token = create_token(context->input_len + 1);
	eat_spaces(context);
	while (s[context->position])
	{
		if (eat_spaces(context))
			break ;
		if (is_quote(s[context->position]))
			if (handle_quote(s + context->position, last_token, context))
				continue ;
		if (is_pipe_or_redir(s[context->position]))
		{
			if (last_token->length > 0)
				break ;
			if (is_double_redir(s[context->position], s[context->position + 1]))
				append_and_shift(last_token, context);
			append_and_shift(last_token, context);
			break ;
		}
		append_and_shift(last_token, context);
	}
	return (finalize_token(last_token));
}

t_token_array	tokenize_input(char *input)
{
	t_token_array	tokens;
	t_lex_context	context;
	t_token			*token;

	if (!init_token_array(&tokens))
		return (tokens);
	init_lex_context(&context, input);
	while (context.position < context.input_len)
	{
		token = get_next_token(&context);
		if (token)
			add_token_to_array(&tokens, token);
	}
	return (tokens);
}
