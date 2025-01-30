#include "../include/minishell.h"

char	*key_value_join(char *key, char *value)
{
	char	*buffer;
	char	*out;

	if (!key || !value)
		return (NULL);
	buffer = ft_strjoin(key, "=");
	out = ft_strjoin(buffer, value);
	free(buffer);
	return (out);
}

int	unset_env(t_env_node **env, char *key)
{
	t_env_node	*loop;

	loop = *env;
	while (loop)
	{
		if (ft_strncmp(loop->env_var, key, strlen(key)) == 0)
		{
			if (loop->previous)
				loop->previous->next = loop->next;
			else
				*env = loop->next;
			if (loop->next)
				loop->next->previous = loop->previous;
			free(loop->env_var);
			free(loop);
			return (1);
		}
		loop = loop->next;
	}
	return (0);
}

static size_t	count_nodes(t_env_node *top)
{
	size_t		count;
	t_env_node	*current;

	count = 0;
	current = top;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static char	**free_nodes(char **env_array, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
		free(env_array[i++]);
	free(env_array);
	return (NULL);
}

char	**lst_to_char(t_env_node *top)
{
	size_t		count;
	size_t		i;
	t_env_node	*current;
	char		**env_array;

	i = 0;
	count = count_nodes(top);
	env_array = (char **)malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	current = top;
	while (i < count)
	{
		env_array[i] = ft_strdup(current->env_var);
		if (!env_array[i])
			return (free_nodes(env_array, i));
		current = current->next;
		i++;
	}
	return (env_array[count] = NULL, env_array);
}
