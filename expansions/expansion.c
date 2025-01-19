#include "../include/minishell.h"


// renvoie la valeur de la variable
// exemple : si $ABC = bonjour, renvoie bonjour
char	*get_env_value(char *to_find, t_program *program)
{
	size_t		i;
	t_env_node	*loop;
	char		*value;

	if (!to_find || !program || !program->envp)
        return (NULL);
	i = ft_strlen(to_find);
	loop = program->envp;
	while (loop)
	{
		if (!ft_strncmp(loop->env_var, to_find, i))
		{
			value = ft_strdup(loop->env_var + i + 1);
			return (value);
		}
		loop = loop->next;
	}
	return (NULL);
}

// Renvoie la taille de la commande apres expansion de toutes les variables
// la fonction get_quote_state permet de savoir quel caractere dans la string est quote
// et avec quel type de quote, ce qui nous permet de realise l'expansion d'une variable uniquement
// si elle n'est pas entre single-quote
// rappel : echo $ABC = echo "$ABC", mais echo '$ABC' = $ABC
int	handle_dollar(size_t *i, char *input,
		t_program *program, t_quote_type *quoting)
{
	size_t	len;
	size_t	size;
	char	*var_name;

	size = ft_strlen(input);
	if (input[*i] == '$' && quoting[*i] != QUOTE_SINGLE)
	{
		(*i)++;
		len = 0;
		while (ft_isalnum(input[*i + len]) || input[*i + len] == '_')
			len++;
		if (len)
		{
			var_name = ft_substr(input, *i, len);
			size = size + get_expanded_var_length(var_name, program) - len - 1;
			free(var_name);
			*i += len;
		}
		return (1);
	}
	return (0);
}

// remplace chaque variable ($ABC) par sa valeur
// si $ est suivi par un caractere non alpha-numerique, on saute simplement
// le $
// par exemple : echo $"PATH" ==> "PATH" ==> PATH (apres quote removal)
char	*expand_command_arg(char *command_arg, t_program *program)
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
	size = get_expanded_arg_size(command_arg, program);
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	quoting = get_quote_state(command_arg);
	if (!quoting)
	{
		free(res);
		return (NULL);
	}
	while (command_arg[i])
	{
		if (command_arg[i] == '$' && quoting[i] != QUOTE_SINGLE)
		{
			i++;
			len = 0;
			while (ft_isalnum(command_arg[i + len]) || command_arg[i + len] == '_')
				len++;
			if (len)
			{
				var_name = ft_substr(command_arg, i, len);
				var_value = get_env_value(var_name, program);
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
	return (res);
}

// Sur chaque commande, on cherche si on trouve un $ et s'il est suivi d'une chaine de caracteres
// pour pouvoir remplace cet ensemble par sa valeur (rien si ce n'est pas une variable d'environnement)
static void	expand_parameters(t_command *command, t_program *program)
{
	size_t	i;
	char	*expanded;
	
	if (!command || !command->argv)
		return ;
	i = 0;
	while (command->argv[i] != NULL)
	{
		expanded = expand_command_arg(command->argv[i], program);
		if (expanded)
		{
			free(command->argv[i]);
			command->argv[i] = expanded;
		}
		i++;
	}
	if (command->redir_in.file && command->redir_in.type != REDIR_HEREDOC) // pas d'expansion si heredoc, car unspecified
	{
		expanded = expand_command_arg(command->redir_in.file, program);
		if (expanded)
		{
			free(command->redir_in.file);
			command->redir_in.file = expanded;
		}
	}
	if (command->redir_out.file)
	{
		expanded = expand_command_arg(command->redir_out.file, program);
		if (expanded)
		{
			free(command->redir_in.file);
			command->redir_in.file = expanded;
		}
	}
}


void	expand_program(t_program *program)
{
	size_t	i;

	if (!program || !program->pipeline || !program->pipeline->commands)
		return ;
	i = 0;
	while (i < program->pipeline->cmd_count) // program->pipeline->commands[i] segfault car déréférencement pointeur NULL
	{
		expand_parameters(program->pipeline->commands[i], program);
		remove_quotes(program->pipeline->commands[i]);
		i++;
	}
}
