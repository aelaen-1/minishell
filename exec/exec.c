 #include "../include/minishell.h"

 static char *get_path(t_command *cmd, t_program *program)
 {
    char **full_path;
    size_t  i;
    char    *path_1;
    char    *path_to_try;

    i = 0;
    full_path = ft_split(get_env_value("PATH", program), ':');
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

int exec_cmd(t_command *cmd, t_program *program)
{
    char    *path;
    path = get_path(cmd, program);
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
    if(!ft_strcmp(cmd->argv[0], "echo"))
        builtin_echo(cmd);
    else if(!ft_strcmp(cmd->argv[0], "env"))
        builtin_env(cmd, program);
    else if(!ft_strcmp(cmd->argv[0], "pwd"))
        builtin_pwd();
    else if(!ft_strcmp(cmd->argv[0], "cd"))
        builtin_cd(cmd, program);
    else if(!ft_strcmp(cmd->argv[0], "export"))
        builtin_export(cmd, program);
    else if(!ft_strcmp(cmd->argv[0], "unset"))
        builtin_unset(cmd, program);
    // enlever infile et outfile de argv pour utiliser exec ??
    else if (execve(path, cmd->argv, NULL) == -1)
    {
        ft_putstr_fd("Could not execute following cmd: ", 2);
        ft_putendl_fd(cmd->argv[0], 2);
        exit(1);
    }
    return (0);
}