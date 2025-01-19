#include "../include/minishell.h"


// Renvoie la taille de la valeur de la variable
// Par exemple : $ABC = bonjour
// la fonction renvoie 7
size_t	get_expanded_var_length(char *var, t_program *program)
{
	char	*value;
	size_t	len;

	value = get_env_value(var, program);
	if (value == NULL)
		return (0);
	len = ft_strlen(value);
	free(value);
	return (len);
}

size_t	get_expanded_arg_size(char *command_arg, t_program *program)
{
	size_t			size;
	size_t			i;
	t_quote_type	*quoting;

	size = ft_strlen(command_arg);
	quoting = get_quote_state(command_arg);
	if (!quoting)
		return (0);
	i = 0;
	while (command_arg[i])
	{
		if (handle_dollar(&i, command_arg, program, quoting))
			continue ;
		i++;
	}
	return (size);
}