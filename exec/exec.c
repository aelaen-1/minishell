#include "../include/minishell.h"


// void exec_cmd(char *cmd)
// {
//     //besoin pour execve()
//     char **split_input = ft_split (cmd, ' ');
//     char *path = get_path(cmd);

//     if (execve(path, split_input, NULL) == -1)
//     {
//         ft_putstr_fd("Command not found : ", STDERR_FILENO);
//         ft_putendl_fd(split_input[0], 2);
//         free_split(split_input);
//         exit(EXIT_FAILURE);
//     }
// }

// le programme s'arrete après une commande sans fork() à chaque appel
void exec_cmd(char *cmd)
{
    pid_t pid;
    int status = 0;
    char *path = get_path(cmd);
    char **split_input = ft_split(cmd, ' ');

    pid = fork();
    if (pid < 0)
        perror("fork err");
    else if (pid > 0)
    { // le parent attend la fin de l'éxecution du processus enfant, pour le tuer
        waitpid(pid, &status, 0);
        kill(pid, SIGTERM);
    }
    else
    {
        if (execve(path, split_input, NULL) == -1)
        {
            ft_putstr_fd("Command not found : ", STDERR_FILENO);
            ft_putendl_fd(split_input[0], 2);
            free_split(split_input);
            exit(EXIT_FAILURE);
        }
    }
}