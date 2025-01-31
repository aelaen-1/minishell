#include "../include/minishell.h"

bool	try_expand_status(char c, t_context *context,
		t_arg_expansion_state *vars)
{
	if (c == '?')
	{
		expand_last_cmd_status(ft_itoa(context->last_cmd_status),
			vars->res, &vars->j, &vars->i);
		return (true);
	}
	return (false);
}

bool	init_arg_expansion_state(t_arg_expansion_state *vars,
		t_context *context, char *arg)
{
	vars->i = 0;
	vars->j = 0;
	vars->len = 0;
	vars->quoting = get_quote_state(arg);
	if (!vars->quoting)
		return (false);
	vars->size = get_expanded_arg_size(&arg, context, vars->quoting);
	if (!vars->size)
	{
		free(vars->quoting);
		vars->res = ft_strdup(" ");
		return (false);
	}
	vars->res = malloc(vars->size + 1);
	if (!vars->res)
	{
		free(vars->quoting);
		return (false);
	}
	return (true);
}
