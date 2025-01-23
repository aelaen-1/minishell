#include "../include/minishell.h"

int	is_valid_identifier(char *arg)
{
	if (!arg || !(*arg) || (!ft_isalpha(*arg) && *arg != '_'))
		return (0);
	while (*arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_' && *arg != '=')
			return (0);
		arg++;
	}
	return (1);
}

static void declare_x(t_env_node *env, t_command *command)
{
    t_env_node *current;
    char *separator;

    current = env;
    while (current)
    {
        if (current->is_exported)
        {
            separator = ft_strchr(current->env_var, '=');
            if (separator)
            {
                ft_putstr_fd("declare -x ", command->fds[1]);
                write(command->fds[1], current->env_var, separator - current->env_var);
                ft_putstr_fd("=\"", command->fds[1]);
                ft_putstr_fd(separator + 1, command->fds[1]);
                ft_putstr_fd("\"\n", command->fds[1]);
            }
            else
            {
                ft_putstr_fd("declare -x ", command->fds[1]);
                ft_putstr_fd(current->env_var, command->fds[1]);
                ft_putstr_fd("\n", command->fds[1]);
            }
        }
        current = current->next;
    }
}

// crée un nouveau node et l'ajoute à la fin de la liste chainée context->envp (env ici)
static void	*create_export_node(t_env_node *env, char *key, char *value)
{
	t_env_node *new_node;
 
	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
		return 0;
	if (!value)
		new_node->env_var = ft_strdup(key);
	else
		new_node->env_var = key_value_join(key, value);
	if(!new_node->env_var)
	{
		free(new_node);
		return 0;
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

static int check_if_exported(char *arg, t_context *context)
{
	t_env_node *current;

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
static void export_key_without_value(char *key, t_context *context)
{
	if (check_if_exported(key, context))
		return ;
	create_export_node(context->envp, key, NULL);
}

static int	export_arg(char *arg, t_context *context)
{
	char *key;
	char *value;
	char *separator;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	separator = ft_strchr(arg, '=');
	if (!separator)
		return (export_key_without_value(arg, context), 0);
	key = ft_substr(arg, 0, separator - arg);
	value = ft_strdup(separator + 1);
	if (!key || !value)
		return (free(key), free(value), 1);
    update_env(&context->envp, key, value);
	return (free(value), free(key), 0);
}

int builtin_export(t_command *command, t_context *context)
{
	int ret;
	int i;

	if (!command->argv[1])
	{
		declare_x(context->envp, command);
		return (0);
	}
	i = 1;
	while (command->argv[i])
	{
		ret = export_arg(command->argv[i], context);
		if (ret)
			break ;
		i++;
	}
	return (ret);
}