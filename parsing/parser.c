#include "../include/minishell.h"

t_program	*parse_program(t_token_array array)
{
	t_program	*program;

	program = malloc(sizeof(t_program));
	if(!program)
		return (0);
	program->pipeline = parse_pipeline(array.tokens,
			array.tokens + array.count);
	if(!program->pipeline)
		return(0);
	return (program);
}
