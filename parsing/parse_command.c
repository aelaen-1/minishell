#include "../include/minishell.h"

void close_command_fds(t_command *command)
{
	if (command->fds[0] != 0 && command->fds[0] != -1)
	{
		close(command->fds[0]);
		command->fds[0] = -1;
	}
	if (command->fds[1] != 1 && command->fds[1] != -1)
	{
		close(command->fds[1]);
		command->fds[1] = -1;
	}
}

// argv est un char ** qui stocke les noms des tokens (les (char *) token->value)
// redir_in est soit de type < soit <<, redir_out est soit > soit >>
// le file associé est le token qui suit la redirection, c'est le nom du fichier qui sert soit d'input soit d'output
// ne traite pas encore s'il y a plusieurs redirections 
t_command	*create_command(size_t argc)
{
	size_t	i;
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->argv = malloc(sizeof(char *) * (argc + 1));
	if (!command->argv)
		return (free(command), NULL);
	i = 0;
	while (i <= argc)
		command->argv[i++] = NULL;
	command->redir_in.type = REDIR_NONE;
	command->redir_out.type = REDIR_NONE;
	command->redir_in.file = NULL;
	command->redir_out.file = NULL;
	command->fds[0] = 0;
	command->fds[1] = 1;
	return (command);
}

// récupère les tokens entre start et end pour les stocker dans command->argv (char **)
// appelle parse_redir() dans la boucle while sur chaque token, pour verifier si le token est une redirection
// et si c'est le cas verifie que le token qui suit est de type WORD, qui sera soit l'infile soit l'outfile selon la redir
t_command	*parse_command(t_token **start, t_token **end)
{
	size_t		argc;
	t_command	*command;
	t_token		**iter;
	size_t		i;
	int			redir;

	i = 0;
	iter = start;
	argc = end - start;
	command = create_command(argc);
	if (!command)
		return 0;
	redir = 0;
	while (iter < end)
	{	
		redir = parse_redir(command, iter, end);
		if (redir == 1)
		{
			iter += 2;
			continue ;
		}
		if (redir == -1)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			return (destroy_command(command), NULL);
		}
		command->argv[i++] = ft_strdup((*iter)->value);
		iter++;
	}
	command->argv[i] = NULL;
	return (command);
}

void	destroy_command(t_command *command)
{
	if (!command)
		return ;
	close_command_fds(command);
	if (command->redir_in.file)
		free(command->redir_in.file);
	if (command->redir_out.file)
		free(command->redir_out.file);
	free_command_argv(command->argv);
	free(command);
}
