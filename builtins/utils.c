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

t_env_node	*create_env_node(char *env_var, t_env_node *bottom)
{
	t_env_node	*new_node;

	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
		return (NULL);
	new_node->env_var = ft_strdup(env_var);
	if (!new_node->env_var)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	new_node->previous = bottom;
	return (new_node);
}

t_env_node	*init_env(char **env)
{
	t_env_node	*top;
	t_env_node	*bottom;
	t_env_node	*new_node;
	int			i;

	top = NULL;
	i = 0;
	bottom = NULL;
	while (env[i])
	{
		new_node = create_env_node(env[i], bottom);
		if (!new_node)
			return (NULL);
		if (!top)
			top = new_node;
		else
			bottom->next = new_node;
		bottom = new_node;
		i++;
	}
	return (top);
}

int	update_existing_env(t_env_node *env, char *key, char *value)
{
	t_env_node	*loop;

	loop = env;
	while (loop)
	{
		if (ft_strncmp(loop->env_var, key, strlen(key)) == 0)
		{
			free(loop->env_var);
			loop->env_var = key_value_join(key, value);
			return (1);
		}
		if (!loop->next)
			break ;
		loop = loop->next;
	}
	return (0);
}

int	add_new_env_node(t_env_node **env, char *key, char *value, t_env_node *loop)
{
	t_env_node	*new_node;

	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
		return (1);
	new_node->env_var = key_value_join(key, value);
	if (!new_node->env_var)
	{
		free(new_node);
		return (2);
	}
	new_node->next = NULL;
	new_node->previous = loop;
	if (loop)
		loop->next = new_node;
	else
		*env = new_node;
	return (3);
}

int	update_env(t_env_node **env, char *key, char *value)
{
	t_env_node	*loop;
	int			result;

	if (!key || !value)
		return (0);
	result = update_existing_env(*env, key, value);
	if (result)
		return (result);
	loop = *env;
	while (loop && loop->next)
		loop = loop->next;
	return (add_new_env_node(env, key, value, loop));
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
