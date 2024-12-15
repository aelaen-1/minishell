#include "../include/minishell.h"

// Fonction qui renvoie le path d'une commande en cherchant dans la variable d'environnement PATH (voir env dans le terminal)

char *get_path(char *cmd)
{
    int i;
    char **split_input;
    char **path_set; 
    char *path;
    char *exec;

    i = 0;
    // récupère tout les chemins possibles listés dans PATH pour ensuite les essayer jusqu'à trouver le bon (s'il la commande existe)
    path_set = ft_split(getenv("PATH"), ':');
    // permet de récupérer le premier élément dans cmd (exemple : si cmd == "ls -l" --> split_input[0] == "ls")
    split_input = ft_split(cmd, ' ');
    while (path_set[i])
    {
        path = ft_strjoin(path_set[i], "/");
        exec = ft_strjoin(path, split_input[0]);
        if (access(exec, F_OK | X_OK) == 0)
        {
            free_split(split_input);
            free_split(path_set);
            free(path);
            return (exec); // on  devra le free
        }
        free(exec);
        free(path);
        i++;
    }
    // free(exec);
    // free(path); sinon pointer being free wasnt allocated
    free_split(path_set);
    free_split(split_input);
    return (cmd);
}
