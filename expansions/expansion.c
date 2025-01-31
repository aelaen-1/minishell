#include "../include/minishell.h"

void	add_expanded_var(char **command_arg, t_arg_expansion_state *vars,
		t_context *context)
{
	char	*var_name;
	char	*var_value;

	if (vars->len != 0)
	{
		var_name = ft_substr(*command_arg, vars->i, vars->len);
		var_value = get_env_value(var_name, context->envp);
		if (var_value)
		{
			ft_strlcpy(vars->res + vars->j,
				var_value, ft_strlen(var_value) + 1);
			vars->j += ft_strlen(var_value);
			free(var_value);
		}
		free(var_name);
		vars->i += vars->len;
	}
}

char	*expand_command_arg(char *command_arg, t_context *context)
{
	t_arg_expansion_state	vars;

	if (!init_arg_expansion_state(&vars, context, command_arg))
		return (vars.res);
	while (command_arg[vars.i])
	{
		if (is_expandable_dollar(command_arg[vars.i],
				command_arg[vars.i + 1], vars.quoting[vars.i]))
		{
			vars.i++;
			if (try_expand_status(command_arg[vars.i], context, &vars))
				continue ;
			vars.len += get_var_len(command_arg + vars.i);
			add_expanded_var(&command_arg, &vars, context);
		}
		else
		{
			vars.res[vars.j] = command_arg[vars.i];
			vars.i++;
			vars.j++;
		}
	}
	return (vars.res[vars.j] = '\0', free(vars.quoting), vars.res);
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
}
