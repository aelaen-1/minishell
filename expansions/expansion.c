#include "../include/minishell.h"

// IMPORTANT : QUOTE REMOVAL

// renvoie la valeur de la variable
// exemple : si $ABC = bonjour, renvoie bonjour
char *get_env_value(char *to_find, t_program *program)
 {
    size_t i;
    t_env_node *loop;

    i = ft_strlen(to_find);
    loop = program->envp;
    while(loop)
    {
        if (!ft_strncmp(loop->env_var, to_find, i))
        {
            char *value;
            value = ft_strdup(loop->env_var + i + 1); // + 1 pour sauter le =
            return (value);
        }
        loop = loop->next;
    }
    return (NULL);
}

// Renvoie la taille de la valeur de la variable
// Par exemple : $ABC = bonjour
// la fonction renvoie 7
static size_t    get_expanded_var_length(char *var, t_program *program)
{
    char *value = get_env_value(var, program);
    if (value == NULL)
        return (0);
    size_t len = ft_strlen(value);
    free(value);
    return (len);
}

// Renvoie la taille de la commande apres expansion de toutes les variables
size_t  get_expanded_arg_size(char **command_arg, t_program *program)
{
    char *input;
    size_t size;
    size_t i;
    size_t len;

    i = 0;
    input = *command_arg;
    size = ft_strlen(input);
    // la fonction get_quote_state permet de savoir quel caractere dans la string est quote
    // et avec quel type de quote, ce qui nous permet de realise l'expansion d'une variable uniquement
    // si elle n'est pas entre single-quote
    // rappel : echo $ABC = echo "$ABC", mais echo '$ABC' = $ABC
    t_quote_type *quoting = get_quote_state(input);
    if (!quoting)
        return (0);
    while (input[i])
    {
        if (input[i] == '$' && quoting[i] != QUOTE_SINGLE)
        {
            i++;
            len = 0;
            while (ft_isalnum(input[i + len]) || input[i + len] == '_')
                len++;
            if (len)
            {
                char *var_name = ft_substr(input, i, len);
                size += get_expanded_var_length(var_name, program) - len - 1; // ajout de la taille de la valeur de la variable, enlève la taille du nom de la variable et du $
                free(var_name);
                i += len; 
            }
        }
        else
            i++;
    }
    return (size);
}

// remplace chaque variable ($ABC) par sa valeur
// si $ est suivi par un caractere non alpha-numerique, on saute simplement
// le $
// par exemple : echo $"PATH" ==> "PATH" ==> PATH (apres quote removal)
char    *expand_command_arg(char **command_arg, t_program *program)
{
    char *input;
    char *res;
    size_t size;
    size_t i;
    size_t j;
    size_t len;

    i = 0;
    j = 0;
    input = *command_arg;
    size = get_expanded_arg_size(command_arg, program); // 1. Calcule la taille de la chaine de caractere apres expansion(s) : $A$B$C par exemple
    // 2. réallocation de la mémoire en fonction de la size obtenue
    res = malloc(size + 1);
    if (!res)
        return (NULL);
    t_quote_type *quoting = get_quote_state(input);
    if (!quoting) 
    {
        free(res);
        return (NULL);
    }
    while (input[i])
    {
        if (input[i] == '$' && quoting[i] != QUOTE_SINGLE)
        {
            i++;
            len = 0;
            while (ft_isalnum(input[i + len]) || input[i + len] == '_')
               len++;
            if (len)
            {
                char *var_name = ft_substr(input, i, len);
                char *var_value = get_env_value(var_name, program);
                if (var_value) // si var_name est le nom d'une variable d'environnement alors on le remplace par sa valeur
                {
                    ft_strlcpy(res + j, var_value, ft_strlen(var_value) + 1); // + 1 = null-terminating the result
                    j += ft_strlen(var_value);
                    free(var_value);
                }
                free(var_name);
                i += len;
            }
        }
        else
            res[j++] = input[i++];
    }
    res[j] = '\0';
    return (res);
}


// Sur chaque commande, on cherche si on trouve un $ et s'il est suivi d'une chaine de caracteres
// pour pouvoir remplace cet ensemble par sa valeur (rien si ce n'est pas une variable d'environnement)
void    perform_expansions(t_command *command, t_program *program)
{
    size_t  i;

    i = 0;
    while (command->argv[i] != NULL)
    {
        char *expanded = expand_command_arg(&command->argv[i], program);
        if (expanded)
        {
            free(command->argv[i]); // réallocation donc on free l'ancienne valeur
            command->argv[i] = expanded;
        }
        i++;
    }
}
