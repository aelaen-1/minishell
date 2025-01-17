#include "../include/minishell.h"

int	init_token_array(t_token_array *array)
{
	array->count = 0;
	array->capacity = 4;
	array->tokens = malloc(array->capacity * sizeof(t_token *));
	return (array->tokens != NULL);
}

void	init_lex_context(t_lex_context *context, char *input)
{
	context->input = input;
	context->input_len = ft_strlen(input);
	context->position = 0;
}
