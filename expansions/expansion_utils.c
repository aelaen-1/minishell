#include "../include/minishell.h"

int	is_expandable_dollar(char c, char d, char quoting)
{
	if (d == '\0')
		return (0);
	if ((c == '$' && quoting != QUOTE_SINGLE) && (ft_isalnum(d) || d == '?'))
		return (1);
	return (0);
}

size_t	get_var_len(char *arg)
{
	size_t	len;

	len = 0;
	while (arg[len] && (ft_isalnum(arg[len]) || arg[len] == '_'))
		len++;
	return (len);
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
		if (!ft_strncmp(envp->env_var, to_find, i) && envp->env_var[i] == '=')
		{
			value = ft_strdup(envp->env_var + i + 1);
			return (value);
		}
		envp = envp->next;
	}
	return (NULL);
}

void	expand_last_cmd_status(char *var_value, char *res, size_t *j, size_t *i)
{
	ft_strlcpy(res + *j, var_value, ft_strlen(var_value) + 1);
	*j += ft_strlen(var_value);
	free(var_value);
	(*i)++;
}

void	remove_null_commands(t_command *command)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (command->argv[i])
	{
		if (*command->argv[i] != '\0')
		{
			command->argv[j] = command->argv[i];
			j++;
		}
		i++;
	}
	command->argv[j] = NULL;
}
