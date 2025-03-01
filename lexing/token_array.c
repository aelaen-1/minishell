#include "../include/minishell.h"

t_token	*create_token(size_t max_size)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_WORD;
	token->length = 0;
	token->value = malloc(max_size);
	if (!token->value)
		return (free(token), NULL);
	ft_bzero(token->value, max_size);
	return (token);
}

t_token	*add_token_to_array(t_token_array *array, t_token *token)
{
	t_token	**new_tokens;

	if (array->count >= array->capacity)
	{
		new_tokens = malloc((array->capacity * 2) * sizeof(t_token *));
		if (!new_tokens)
		{
			free(token->value);
			free(token);
			return (NULL);
		}
		ft_memcpy(new_tokens, array->tokens, array->count * sizeof(t_token *));
		free(array->tokens);
		array->tokens = new_tokens;
		array->capacity *= 2;
	}
	array->tokens[array->count] = token;
	array->count++;
	return (token);
}

void	find_token_type(t_token *token)
{
	if (!ft_strcmp(token->value, "|"))
		token->type = TOKEN_PIPE;
	else if (!ft_strcmp(token->value, "<"))
		token->type = TOKEN_REDIR_IN;
	else if (!ft_strcmp(token->value, ">"))
		token->type = TOKEN_REDIR_OUT;
	else if (!ft_strcmp(token->value, "<<"))
		token->type = TOKEN_HEREDOC;
	else if (!ft_strcmp(token->value, ">>"))
		token->type = TOKEN_APPEND;
	else
		token->type = TOKEN_WORD;
}
