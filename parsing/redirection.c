#include "../include/minishell.h"

// heredoc
// do 
// { 
//  line = readline();
// } while (strcmp(line, redir_in.file) != 0);

void    redirect_cmd(t_command *command)
{
    if (command->redir_in.file && command->redir_in.type == REDIR_IN)
    {
        command->fds[0] = open(command->redir_in.file, O_RDONLY);
        if (command->fds[0] == -1) // utiliser commande access
            fprintf(stderr, "minishell: %s: Failed to open file for reading\n", command->redir_in.file);
    }
    // if (command->redir_in.file && command->redir_in.type == REDIR_HEREDOC)
    // {
    //     // handle_heredoc();
    // }
    if (command->redir_out.file && command->redir_out.type == REDIR_OUT)
    {
        command->fds[1] = open(command->redir_out.file, O_RDWR | O_CREAT | O_TRUNC);
        if (command->fds[1] == -1)
            fprintf(stderr, "minishell: %s: Failed to open file for writing\n", command->redir_in.file);
    }
    if (command->redir_out.file && command->redir_out.type == REDIR_APPEND)
    {
        command->fds[1] = open(command->redir_out.file, O_RDWR | O_CREAT | O_APPEND);
        if (command->fds[1] == -1)
            fprintf(stderr, "minishell: %s: Failed to open file for writing\n", command->redir_in.file);
    }
}

void    redirect_program(t_program *program)
{
    size_t  i;

    i = 0;
    while (i < program->pipeline->cmd_count)
    {
        redirect_cmd(program->pipeline->commands[i]);
        i++;
    }
}