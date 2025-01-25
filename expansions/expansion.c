#include "../include/minishell.h"
// waitpid status pour la valeur de $?

static void	expand_last_cmd_status(char *var_value, char *res, size_t *j, size_t *i)
{
	ft_strlcpy(res + *j, var_value, ft_strlen(var_value) + 1);
	*j += ft_strlen(var_value);
	free(var_value);
	(*i)++;
}

char	*get_env_value(char *to_find, t_env_node *envp)
{
	size_t		i;
	char		*value;

	if (!to_find || !envp)
        return (NULL);
	i = ft_strlen(to_find);
	while (envp)
	{
		if (!ft_strncmp(envp->env_var, to_find, i ) && envp->env_var[i] == '=')
		{
			value = ft_strdup(envp->env_var + i + 1);
			return (value);
		}
		envp = envp->next;
	}
	return (NULL);
}

// remplace chaque variable ($ABC) par sa valeur
// si $ est suivi par un caractere non alpha-numerique, on saute simplement
// le $
// par exemple : echo $"PATH" ==> "PATH" ==> PATH (apres quote removal)
char	*expand_command_arg(char *command_arg, t_context *context)
{
	char			*res;
	size_t			size;
	size_t			i;
	size_t			j;
	size_t			len;
	t_quote_type	*quoting;
	char			*var_name;
	char			*var_value;

	i = 0;
	j = 0;
	quoting = get_quote_state(command_arg);
	if (!quoting)
		return (NULL);
	size = get_expanded_arg_size(command_arg, context, quoting);
	res = malloc(size + 1);
	if (!res)
		return (free(quoting), NULL);
	while (command_arg[i])
	{
		if (command_arg[i] == '$' && quoting[i] != QUOTE_SINGLE && command_arg[i + 1])
		{
			i++;
			len = 0;
			if (command_arg[i] == '?')
			{
				expand_last_cmd_status(ft_itoa(context->last_cmd_status), res, &j, &i);
				continue;
			}
			while (ft_isalnum(command_arg[i + len]) || command_arg[i + len] == '_')
				len++;
			if (len)
			{
				var_name = ft_substr(command_arg, i, len);
				var_value = get_env_value(var_name, context->envp);
				if (var_value)
				{
					ft_strlcpy(res + j, var_value, ft_strlen(var_value) + 1);
					j += ft_strlen(var_value);
					free(var_value);
				}
				free(var_name);
				i += len;
			}
		}
		else
			res[j++] = command_arg[i++];
	}
	res[j] = '\0';
	free(quoting);
	return (res);
}

// Sur chaque commande, on cherche si on trouve un $ et s'il est suivi d'une chaine de caracteres
// pour pouvoir remplace cet ensemble par sa valeur (rien si ce n'est pas une variable d'environnement)
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
	if (command->redir_in.file && command->redir_in.type != REDIR_HEREDOC) // pas d'expansion si heredoc, car unspecified
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

void	expand_command(t_command *command, t_context *context)
{
	expand_parameters(command, context);
	remove_quotes(command);
}
