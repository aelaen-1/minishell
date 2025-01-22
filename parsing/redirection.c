#include "../include/minishell.h"

static void handle_heredoc(t_command *command)
{
    int pipe_fds[2];

    pipe(pipe_fds);
    command->fds[0] = pipe_fds[0];
    char *line;
    while (1)
    {
        line = readline("> ");
        if (line == NULL || !ft_strcmp(line, command->redir_in.file))
            break ;
        ft_putstr_fd(line, pipe_fds[1]);
        ft_putchar_fd('\n', pipe_fds[1]);
    }
}
void    redirect_command(t_command *command)
{
    if (command->redir_in.file && command->redir_in.type == REDIR_IN)
    {
        command->fds[0] = open(command->redir_in.file, O_RDONLY);
        if (command->fds[0] == -1) // utiliser commande access
            fprintf(stderr, "minishell: %s: Failed to open file for reading\n", command->redir_in.file);
    }
    if (command->redir_in.file && command->redir_in.type == REDIR_HEREDOC)
        handle_heredoc(command);
    if (command->redir_out.file && command->redir_out.type == REDIR_OUT)
    {
        command->fds[1] = open(command->redir_out.file, O_RDWR | O_CREAT | O_TRUNC, 0777);
        if (command->fds[1] == -1)
            fprintf(stderr, "minishell: %s: Failed to open file for writing\n", command->redir_in.file);
    }
    if (command->redir_out.file && command->redir_out.type == REDIR_APPEND)
    {
        command->fds[1] = open(command->redir_out.file, O_RDWR | O_CREAT | O_APPEND, 0777);
        if (command->fds[1] == -1)
            fprintf(stderr, "minishell: %s: Failed to open file for writing\n", command->redir_in.file);
    }
}