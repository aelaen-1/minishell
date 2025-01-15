#include "../include/minishell.h"

// Par l 'exemple
// ls -l infile > outfile | wc

// First arg == cmd "ls -l"
//  1 - On cherche cette commande avec access() :
//  2 - On duplique stdin et stdout s'il y un input et/ou output precises (ici infile et outfile)

 // 1

 static char *get_path(t_command *cmd)
 {
    char **full_path;
    size_t  i;
    char    *path_1;
    char    *path_to_try;

    i = 0;
    full_path = ft_split(get_env_value(cmd, "PATH"), ':');
    while (full_path[i])
    {
        path_1 = ft_strjoin(full_path[i], "/");
        path_to_try = ft_strjoin(path_1, cmd->argv[0]);
        if (access(path_to_try, F_OK | X_OK) == 0)
        {
            free(path_1);
            return (path_to_try);
        }
        free(path_1);
        free(path_to_try);
        i++;
    }
    if (!full_path[i])
        ft_putstr_fd("Path not found\n", 2);
    return (NULL); 
 }

int exec_cmd(t_command *cmd, char **env)
{
    char    *path;
    path = get_path(cmd);
    if (!path)
        return (-1); // afficher un code d'erreur
    // duplication de fd selon infile/outfile
    if (cmd->redir_in.type != REDIR_NONE)
    {
        if (cmd->redir_in.type == REDIR_IN)
        {
            int fd_infile = open(cmd->redir_in.file, O_RDONLY);
            if (fd_infile == -1)
            {
                ft_putstr_fd("Infile not found\n", 2);
                return 0;
            }
            dup2(fd_infile, 0);
        }
        //else here_doc 
    }
    if (cmd->redir_out.type != REDIR_NONE)
    {
        if (cmd->redir_out.type == REDIR_OUT)
        {
            int fd_outfile = open(cmd->redir_out.file, O_RDWR | O_CREAT | O_TRUNC);
            if (fd_outfile == -1)
            {
                ft_putstr_fd("Outfile not found\n", 2);
                return 0;
            }
            dup2(fd_outfile, 1);
        }
        else // REDIR_APPEND
        {
            int fd_outfile = open(cmd->redir_in.file, O_RDWR | O_APPEND);
            if (fd_outfile == -1)
            {
                ft_putstr_fd("Outfile not found\n", 2);
                return 0;
            }
            dup2(fd_outfile, 1);
        }
    }  
    // enlever infile et outfile de argv pour utiliser exec ??
    if (execve(path, cmd->argv, env) == -1)
    {
        ft_putstr_fd("Could not execute following cmd: ", 2);
        ft_putendl_fd(cmd->argv[0], 2);
        exit(1);
    }
    return (0);
}