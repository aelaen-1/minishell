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

static void	declare_env_var(t_env_node *current, int fd)
{
	char	*separator;

	separator = ft_strchr(current->env_var, '=');
	if (separator)
	{
		ft_putstr_fd("export ", fd);
		write(fd, current->env_var, separator - current->env_var);
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(separator + 1, fd);
		ft_putstr_fd("\"\n", fd);
	}
	else
	{
		ft_putstr_fd("export ", fd);
		ft_putstr_fd(current->env_var, fd);
		ft_putstr_fd("\n", fd);
	}
}

static void	declare_x(t_env_node *env, t_command *command)
{
	t_env_node	*current;

	current = env;
	while (current)
	{
		if (current->is_exported)
		{
			declare_env_var(current, command->fds[1]);
		}
		current = current->next;
	}
}

static int	export_arg(char *arg, t_context *context)
{
	char	*key;
	char	*value;
	char	*separator;

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

int	builtin_export(t_command *command, t_context *context)
{
	int	ret;
	int	i;

	if (!command->argv[1])
		declare_x(context->envp, command);
	i = 1;
	while (command->argv[i])
	{
		ret = export_arg(command->argv[i], context);
		if (ret)
			return (1);
		i++;
	}
	return (0);
}
