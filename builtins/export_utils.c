#include "../include/minishell.h"

void	*create_export_node(t_env_node *env, char *key, char *value)
{
	t_env_node	*new_node;

	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
		return (0);
	if (!value)
		new_node->env_var = ft_strdup(key);
	else
		new_node->env_var = key_value_join(key, value);
	if (!new_node->env_var)
	{
		free(new_node);
		return (0);
	}
	new_node->is_exported = true;
	while (env->next)
		env = env->next;
	if (env)
		env->next = new_node;
	new_node->next = NULL;
	new_node->previous = env;
	return (0);
}

int	check_if_exported(char *arg, t_context *context)
{
	t_env_node	*current;

	current = context->envp;
	while (current)
	{
		if (!ft_strncmp(current->env_var, arg, ft_strlen(arg)))
		{
			current->is_exported = true;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	export_key_without_value(char *key, t_context *context)
{
	if (check_if_exported(key, context))
		return ;
	create_export_node(context->envp, key, NULL);
}
