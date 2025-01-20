#include "../include/minishell.h"

<<<<<<< HEAD
// to do 

=======
>>>>>>> 9ae4ba0 (giterr)
static char	*get_var_end(char *start)
{
	char *iter;

	if (!start)
		return (NULL);
	iter = start;
	while (ft_isalnum(*iter)|| *iter == '_')
		iter++;
	if (iter == start)
		return (NULL);
	return (iter);
}	
static size_t	get_expanded_var_length(char *var, t_context *context)
{
	char	*value;
	size_t	len;

	if (ft_strcmp(var, "?") == 0)
	{
		return (get_number_length(context->last_cmd_status));
	}
	value = get_env_value(var, context->envp);
	if (value == NULL)
		return (0);
	len = ft_strlen(value);
	free(value);
	return (len);
}


static char *handle_dollar(char *dollar, t_context *context, size_t *size_out)
{
	char *end;
	char *start;
			
	start = dollar + 1;
	end = get_var_end(start);
	if (end)
	{	
		char	*var_name;
		size_t	len;

		len = end - start;
		var_name = ft_substr(start, 0, len);
		*size_out += get_expanded_var_length(var_name, context) - len - 1;
		free(var_name);
		return (end);
	}
	return (start);
}

size_t	get_expanded_arg_size(char *command_arg, t_context *context, t_quote_type *quoting)
{
	size_t			size;
	char			*iter;

	size = ft_strlen(command_arg);
	iter = command_arg;
	while (*iter)
	{
		if (*iter == '$' && quoting[iter-command_arg] != QUOTE_SINGLE)
			iter = handle_dollar(iter, context, &size);
		else
			iter++;
	}
	return (size);
}
