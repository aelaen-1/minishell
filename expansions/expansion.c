#include "../include/minishell.h"


void	add_expanded_var(char **command_arg, char **res, size_t *i, size_t *j, size_t *len, t_context *context)
{
	char *var_name;
	char *var_value;

	if (*len != 0)
		{
			var_name = ft_substr(*command_arg, *i, *len);
			var_value = get_env_value(var_name, context->envp);
			if (var_value)
			{
				ft_strlcpy(*res + *j, var_value, ft_strlen(var_value) + 1);
				*j += ft_strlen(var_value);
				free(var_value);
			}
			free(var_name);
			*i += *len;
		}
}

// bool try_expand_status(t_context *context, char *res, int* i_ptr, int *j_ptr)
// {
//   if (command_arg[*i_ptr] == '?')
//   {
//     expand_last_cmd_status(ft_itoa(context->last_cmd_status), res, j_ptr, i_ptr);
//     return true;
//   }
//   return false;
// }

char	*expand_command_arg(char *command_arg, t_context *context)
{
	char			*res;
	size_t			size;
	size_t			i;
	size_t			j;
	size_t			len;
	t_quote_type	*quoting;

	i = 0;
	j = 0;
	quoting = get_quote_state(command_arg);
	if (!quoting)
		return (NULL);
	size = get_expanded_arg_size(&command_arg, context, quoting);
	// if (!size)
	// 	return (free(quoting), NULL);
	res = malloc(size + 1);
	if (!res)
		return (free(quoting), NULL);
	while (command_arg[i])
	{
		if (is_expandable_dollar(command_arg[i], command_arg[i + 1], quoting[i]))
		{
			i++;
			len = 0;
			// if (try_expand_status(context, res, &j, &i))
			// 	continue ;
			if (command_arg[i] == '?')
			{
				expand_last_cmd_status(ft_itoa(context->last_cmd_status), res, &j, &i);
				continue;
			}
			len += get_var_len(command_arg + i);
			add_expanded_var(&command_arg, &res, &i, &j, &len, context);
		}
		else
			res[j++] = command_arg[i++];
	}
	return (res[j] = '\0', free(quoting), res);
}



void	expand_redir(t_command *command, t_context *context)
{
	char	*expanded;
	
	if (!command || !command->argv)
		return ;
	
	if (command->redir_in.file && command->redir_in.type != REDIR_HEREDOC)
	{
		expanded = expand_command_arg(command->redir_in.file, context);
		if (expanded)
		{
			free(command->redir_in.file);
			command->redir_in.file = expanded;
		}
	}
	if (command->redir_out.file)
	{
		expanded = expand_command_arg(command->redir_out.file, context);
		if (expanded)
		{
			free(command->redir_out.file);
			command->redir_out.file = expanded;
		}
	}
}

static void	expand_parameters(t_command *command, t_context *context)
{
	size_t	i;
	char	*expanded;
	
	if (!command || !command->argv)
		return ;
	i = 0;
	while (command->argv[i] != NULL)
	{
		expanded = expand_command_arg(command->argv[i], context);
		if (expanded)
		{
			free(command->argv[i]);
			command->argv[i] = expanded;
		}
		i++;
	}
}

void	expand_command(t_command *command, t_context *context)
{
	expand_parameters(command, context);
	expand_redir(command, context);
	remove_null_commands(command);
	remove_quotes(command);
	printf("expanded : %s\n", command->argv[0]);
}
