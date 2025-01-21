#include "../include/minishell.h"

// cree un programme constitue d'une pipeline et de ses commandes  
// exemple : ls -a folder/ | wc -l | grep "1" : un pipeline, trois commandes
// s'il n'y a qu'une commande, program->pipeline est egale a la commande saisie 
// parse_pipeline() appelle parse_command() qui appelle parse_redir()
t_program	*parse_program(t_token_array array)
{
	t_program	*program;

	program = malloc(sizeof(t_program));
	if(!program)
		return (0);
	program->pipeline = parse_pipeline(array.tokens,
			array.tokens + array.count, program);
	if(!program->pipeline)
		return(0);

	return (program);
}
