#include "../include/minishell.h"

// argv est un char ** qui stocke les noms des tokens (les (char *) token->value)
// redir_in est soit de type < soit <<, redir_out est soit > soit >>
// le file associé est le token qui suit la redirection, c'est le nom du fichier qui sert soit d'input soit d'output
// ne traite pas encore s'il y a plusieurs redirections 
t_command	*create_command(int argc)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->argv = malloc(sizeof(char *) * (argc + 1));
	if (!command->argv)
		return (free(command), NULL);
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
t_command	*parse_command(t_token **start, t_token **end, t_program *program)
{
	size_t		argc;
	t_command	*command;
	t_token		**iter;
	size_t		i;

	i = 0;
	iter = start;
	argc = end - start;
	(void)program;
	command = create_command(argc);
	if (!command)
		return 0;
	while (iter < end)
	{
		if (parse_redir(command, iter))
			iter += 2;
		else
		{
			command->argv[i++] = ft_strdup((*iter)->value);
			iter++;
		}
	}
	command->argv[i] = NULL;
	return (command);
}

// free proprement ce que l'on a cree avec create_command
// et dans la fonction parse_redir (strdup sur redir_in et redir_out)
void	destroy_command(t_command *command)
{
	if (!command)
		return ;
	if (command->fds[0] != 0)
		close(command->fds[0] && command->fds[0] != -1);
	if (command->fds[1] != 1 && command->fds[1] != -1)
		close(command->fds[1]);
	free(command->redir_in.file);
	free(command->redir_out.file);
	free(command->argv); // les argv[i] sont free dans free_command
	free(command);
}
