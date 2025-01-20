#include "../include/minishell.h"

static void	remove_str_quotes(char *str)
{
	t_quote_type	*quote_state;
	t_quote_type	current;
	size_t			i;
	size_t			j;

	current = QUOTE_NONE;
	quote_state = get_quote_state(str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (quote_state[i] != current)
		{
			current = quote_state[i];
			i++;
			if (!str[i])
				break ;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
	free(quote_state);
}

void	remove_quotes(t_command *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->argv[i])
	{
		remove_str_quotes(cmd->argv[i]);
		i++;
	}
	if (cmd->redir_in.file)
		remove_str_quotes(cmd->redir_in.file);
	if (cmd->redir_out.file)
		remove_str_quotes(cmd->redir_out.file);
}