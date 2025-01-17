#include "../include/minishell.h"

// renvoie la valeur de la variable
// exemple : si $ABC = bonjour, renvoie bonjour
char	*get_env_value(char *to_find, t_program *program)
{
	size_t		i;
	t_env_node	*loop;
	char		*value;

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

// Renvoie la taille de la valeur de la variable
// Par exemple : $ABC = bonjour
// la fonction renvoie 7
static size_t	get_expanded_var_length(char *var, t_program *program)
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
			size += get_expanded_var_length(var_name, program) - len - 1;
			free(var_name);
			*i += len;
		}
		return (1);
	}
	return (0);
}

size_t	get_expanded_arg_size(char **command_arg, t_program *program)
{
	char			*input;
	size_t			size;
	size_t			i;
	t_quote_type	*quoting;

	input = *command_arg;
	size = ft_strlen(input);
	quoting = get_quote_state(input);
	if (!quoting)
		return (0);
	i = 0;
	while (input[i])
	{
		if (handle_dollar(&i, input, program, quoting))
			continue ;
		i++;
	}
	return (size);
}

// remplace chaque variable ($ABC) par sa valeur
// si $ est suivi par un caractere non alpha-numerique, on saute simplement
// le $
// par exemple : echo $"PATH" ==> "PATH" ==> PATH (apres quote removal)
char	*expand_command_arg(char **command_arg, t_program *program)
{
	char			*input;
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
	input = *command_arg;
	size = get_expanded_arg_size(command_arg, program);
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	quoting = get_quote_state(input);
	if (!quoting)
	{
		free(res);
		return (NULL);
	}
	while (input[i])
	{
		if (input[i] == '$' && quoting[i] != QUOTE_SINGLE)
		{
			i++;
			len = 0;
			while (ft_isalnum(input[i + len]) || input[i + len] == '_')
				len++;
			if (len)
			{
				var_name = ft_substr(input, i, len);
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
			res[j++] = input[i++];
	}
	res[j] = '\0';
	return (res);
}

// Sur chaque commande, on cherche si on trouve un $ et s'il est suivi d'une chaine de caracteres
// pour pouvoir remplace cet ensemble par sa valeur (rien si ce n'est pas une variable d'environnement)
void	perform_expansions(t_command *command, t_program *program)
{
	size_t	i;
	char	*expanded;
	
	i = 0;
	while (command->argv[i] != NULL)
	{
		expanded = expand_command_arg(&command->argv[i], program);
		if (expanded)
		{
			free(command->argv[i]);
			command->argv[i] = expanded;
		}
		i++;
	}
}
