#include "../include/minishell.h"

t_program	*parse_program(t_token_array array)
{
	t_program	*program;

	if (array.count == 0)
		return (NULL);
	program = malloc(sizeof(t_program));
	if(!program)
		return (NULL);
	program->pipeline = parse_pipeline(array.tokens,
			array.tokens + array.count);
	if(!program->pipeline)
		return(free(program), NULL);
	return (program);
}
